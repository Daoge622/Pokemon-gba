// Explicitly authorized, isolated mGBA runtime probe. Never opens a GUI or writes its input save.
// Include installed build flags before core headers so the library ABI matches.
#include <mgba/flags.h>
#include <mgba/core/core.h>
#include <mgba/core/config.h>
#include <mgba/core/serialize.h>
#include <mgba/internal/arm/arm.h>
#include <mgba-util/vfs.h>
#include <mgba/core/log.h>
#include <mgba/internal/gba/gba.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void quiet(struct mLogger *l,int cat,enum mLogLevel level,const char *format,va_list args){}
struct sym {char name[180]; unsigned addr;};
struct sym syms[500000];int ns;
unsigned watchObjects;int lastX[16],lastY[16];
void probeFrame(struct mCore *c){
 c->runFrame(c);
 if(!watchObjects)return;
 for(int i=0;i<16;i++){
  unsigned a=watchObjects+36*i,id=c->busRead8(c,a+8);
  if(!(c->busRead8(c,a)&1)||(id!=5&&id!=7))continue;
  int x=(short)c->busRead16(c,a+16)-7,y=(short)c->busRead16(c,a+18)-7;
  if(x!=lastX[i]||y!=lastY[i]){printf("actor %u xy=%d,%d frame=%u\n",id,x,y,c->frameCounter(c));lastX[i]=x;lastY[i]=y;}
  if(x==10&&y==4){fprintf(stderr,"FAIL rescue actor %u crosses barrier\n",id);exit(13);}
 }
}
unsigned val(char *s){if(s[0]=='0'||(s[0]>='1'&&s[0]<='9'))return strtoul(s,0,0);for(int i=0;i<ns;i++)if(!strcmp(s,syms[i].name))return syms[i].addr;fprintf(stderr,"Unknown %s\n",s);exit(2);}
unsigned call(struct mCore *c,unsigned f,unsigned *args,int n){
 struct ARMCore *cpu=c->cpu;int safety=0;
 while((cpu->cpsr.packed&31)!=31 && safety++<100000)c->step(c);
 int32_t saved[16];memcpy(saved,cpu->gprs,sizeof(saved));unsigned psr=cpu->cpsr.packed,pref[2];memcpy(pref,cpu->prefetch,8);enum ExecutionMode mode=cpu->executionMode;
 unsigned cp=psr|32; c->writeRegister(c,"cpsr",&cp);
 unsigned sp=0x03007c00;c->writeRegister(c,"sp",&sp);
 for(int i=0;i<n;i++){if(i<4){char r[3];sprintf(r,"r%d",i);c->writeRegister(c,r,&args[i]);}else c->busWrite32(c,sp+4*(i-4),args[i]);}
 unsigned lr=0x08000001;c->writeRegister(c,"lr",&lr);unsigned pc=f&~1;c->writeRegister(c,"pc",&pc);
 int steps;for(steps=0;steps<3000000;steps++){if((cpu->gprs[15]&~3)==0x08000000)break;c->step(c);}
 unsigned result=cpu->gprs[0];if(steps==3000000){fprintf(stderr,"Call timeout pc=%08x fn=%08x\n",cpu->gprs[15],f);exit(3);}
 c->writeRegister(c,"cpsr",&psr);memcpy(cpu->gprs,saved,sizeof(saved));memcpy(cpu->prefetch,pref,8);cpu->executionMode=mode;cpu->memory.setActiveRegion(cpu,saved[15]);return result;
}
int main(int argc,char **argv){if(argc<5||strcmp(argv[1],"--allow-rom-execution")){fprintf(stderr,"Explicit ROM execution authorization required. Use the QA driver.\\n");return 2;}argc--;argv++;if(argc<4)return 2;FILE *s=fopen(argv[2],"r");char line[512];while(fgets(line,sizeof(line),s)){unsigned a;char type,name[180];if(sscanf(line,"%x %c %179s",&a,&type,name)==3&&ns<500000){strcpy(syms[ns].name,name);syms[ns++].addr=a|((type=='t'||type=='T')?1:0);}}fclose(s);
struct mLogger logger={.log=quiet};mLogSetDefaultLogger(&logger);struct mCore *c=mCoreFind(argv[1]);if(!c||!c->init(c))return 3;mCoreInitConfig(c,"isolated-runtime-qa");color_t *pixels=calloc(240*160,sizeof(color_t));c->setVideoBuffer(c,pixels,240);if(!mCoreLoadFile(c,argv[1]))return 4;
unsigned char initialSave[131072];memset(initialSave,255,sizeof(initialSave));if(argc>4){FILE *sf=fopen(argv[4],"rb");if(!sf)return 5;if(fread(initialSave,1,sizeof(initialSave),sf)!=sizeof(initialSave))return 5;fclose(sf);}struct VFile *saveVF=VFileMemChunk(initialSave,sizeof(initialSave));if(!saveVF||!c->loadSave(c,saveVF))return 5;
c->reset(c);FILE *cmd=fopen(argv[3],"r");setbuf(stdout,NULL);
while(fgets(line,sizeof(line),cmd)){char *tok[16],*p=strtok(line," \t\r\n");int n=0;while(p&&n<16){tok[n++]=p;p=strtok(NULL," \t\r\n");}if(!n||tok[0][0]=='#')continue;
 if(!strcmp(tok[0],"frames")){int k=n>2?val(tok[2]):0;c->setKeys(c,k);for(int i=0;i<atoi(tok[1]);i++)probeFrame(c);c->setKeys(c,0);}
 else if(!strcmp(tok[0],"wait")){unsigned a=val(tok[1]),v=val(tok[2]),limit=atoi(tok[3]),key=n>4?val(tok[4]):0;unsigned i;for(i=0;i<limit;i++){if(c->busRead32(c,a)==v)break;c->setKeys(c,(i%20<4)?key:0);probeFrame(c);}c->setKeys(c,0);printf("wait %s=%08x frames=%u actual=%08x %s\n",tok[1],v,i,c->busRead32(c,a),i==limit?"TIMEOUT":"PASS");}
else if(!strcmp(tok[0],"zero")){unsigned a=val(tok[1]),size=val(tok[2]);if(a<0x02000000||a+size>0x02040000)return 12;for(unsigned i=0;i<size;i++)c->busWrite8(c,a+i,0);}
else if(!strcmp(tok[0],"ptrwrite")){unsigned a=c->busRead32(c,val(tok[1]))+val(tok[2]),v=val(tok[3]),b=n>4?val(tok[4]):4;if(a<0x02000000||a+b>0x02040000)return 12;if(b==1)c->busWrite8(c,a,v);else if(b==2)c->busWrite16(c,a,v);else c->busWrite32(c,a,v);}
else if(!strcmp(tok[0],"ptrcall")){unsigned args[12];args[0]=c->busRead32(c,val(tok[2]))+val(tok[3]);for(int i=4;i<n;i++)args[i-3]=val(tok[i]);printf("ptrcall %s = %08x\n",tok[1],call(c,val(tok[1]),args,n-3));}
else if(!strcmp(tok[0],"watch")){watchObjects=val(tok[1]);for(int i=0;i<16;i++){lastX[i]=-999;lastY[i]=-999;}}
else if(!strcmp(tok[0],"copy")){unsigned d=val(tok[1]),s=val(tok[2]),size=val(tok[3]);if(size>1200||d<0x02000000||d+size>0x02040000||s<0x02000000||s+size>0x02040000)return 12;unsigned char buf[1200];for(unsigned i=0;i<size;i++)buf[i]=c->busRead8(c,s+i);for(unsigned i=0;i<size;i++)c->busWrite8(c,d+i,buf[i]);}
else if(!strcmp(tok[0],"expectcall")){unsigned args[12];for(int i=3;i<n;i++)args[i-3]=val(tok[i]);unsigned got=call(c,val(tok[1]),args,n-3),want=val(tok[2]);if(got!=want){fprintf(stderr,"FAIL call %s got=%08x expected=%08x\n",tok[1],got,want);return 10;}printf("PASS call %s=%08x\n",tok[1],got);}
else if(!strcmp(tok[0],"call")){unsigned args[12];for(int i=2;i<n;i++)args[i-2]=val(tok[i]);printf("call %s = %08x\n",tok[1],call(c,val(tok[1]),args,n-2));}
 else if(!strcmp(tok[0],"read")){unsigned a=val(tok[1]),b=n>2?atoi(tok[2]):4;printf("read %s=0x%08x\n",tok[1],b==1?c->busRead8(c,a):b==2?c->busRead16(c,a):c->busRead32(c,a));}
 else if(!strcmp(tok[0],"write")){unsigned a=val(tok[1]),v=val(tok[2]),b=n>3?atoi(tok[3]):4;if(b==1)c->busWrite8(c,a,v);else if(b==2)c->busWrite16(c,a,v);else c->busWrite32(c,a,v);}
 else if(!strcmp(tok[0],"screen")){struct VFile *vf=VFileOpen(tok[1],O_WRONLY|O_CREAT|O_TRUNC);if(!vf||!mCoreTakeScreenshotVF(c,vf))return 6;vf->close(vf);}
 else if(!strcmp(tok[0],"state")){struct VFile *vf=VFileOpen(tok[1],O_RDWR|O_CREAT|O_TRUNC);if(!vf||!mCoreSaveStateNamed(c,vf,0))return 7;vf->close(vf);}
 else if(!strcmp(tok[0],"load")){struct VFile *vf=VFileOpen(tok[1],O_RDONLY);if(!vf||!mCoreLoadStateNamed(c,vf,0))return 8;vf->close(vf);}
 else if(!strcmp(tok[0],"save")){void *data=NULL;size_t size=c->savedataClone(c,&data);printf("save type=%d data=%p size=%zu\n",((struct GBA*)c->board)->memory.savedata.type,((struct GBA*)c->board)->memory.savedata.data,size);FILE *vf=fopen(tok[1],"wb");if(!vf||!data||!size)return 11;fwrite(data,1,size,vf);fclose(vf);free(data);printf("saved %zu bytes\n",size);}
else if(!strcmp(tok[0],"expect")){unsigned a=val(tok[1]),want=val(tok[2]),b=n>3?atoi(tok[3]):4,mask=n>4?val(tok[4]):0xffffffff;unsigned got=b==1?c->busRead8(c,a):b==2?c->busRead16(c,a):c->busRead32(c,a);if((got&mask)!=want){fprintf(stderr,"FAIL expect %s got=%08x expected=%08x mask=%08x\n",tok[1],got,want,mask);return 10;}printf("PASS expect %s=%08x\n",tok[1],got);}
else if(!strcmp(tok[0],"status")){struct ARMCore *cpu=c->cpu;printf("frame=%u pc=%08x lr=%08x cpsr=%08x\n",c->frameCounter(c),cpu->gprs[15],cpu->gprs[14],cpu->cpsr.packed);}
 else {fprintf(stderr,"Unknown command %s\n",tok[0]);return 9;}
}fclose(cmd);printf("Complete frames=%u\n",c->frameCounter(c));c->unloadROM(c);mCoreConfigDeinit(&c->config);c->deinit(c);free(pixels);return 0;}