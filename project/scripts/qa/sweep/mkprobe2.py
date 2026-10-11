import os
src = os.path.expanduser('~/projects/emerald-story/scripts/qa/gameplay-probe.c')
dst = os.path.expanduser('~/qa-sweep/probe2.c')
s = open(src).read()
a = "static void quiet(struct mLogger *l,int cat,enum mLogLevel level,const char *format,va_list args){}"
b = r'''static void quiet(struct mLogger *l,int cat,enum mLogLevel level,const char *format,va_list args){
 const char *cn=mLogCategoryName(cat);
 if(!cn)return;
 if(strstr(cn,"Debug")||strstr(cn,"debug")||level&(mLOG_FATAL|mLOG_ERROR)){fprintf(stdout,"LOG[%s:%d] ",cn,level);vfprintf(stdout,format,args);fprintf(stdout,"\n");}
}'''
assert a in s
s = s.replace(a, b)
a2 = 'else if(!strcmp(tok[0],"status"))'
assert a2 in s
s = s.replace(a2, 'else if(!strcmp(tok[0],"mark")){printf("MARK %s\\n",tok[1]);}\n'
              'else if(!strcmp(tok[0],"stackfill")){unsigned lo=val(tok[1]),hi=((struct ARMCore*)c->cpu)->gprs[13]-64;if(n>2)hi=val(tok[2]);for(unsigned a=lo;a<hi;a+=4)c->busWrite32(c,a,0xC0FFEE11);printf("stackfill %08x..%08x sp=%08x\\n",lo,hi,((struct ARMCore*)c->cpu)->gprs[13]);}\n'
              'else if(!strcmp(tok[0],"stackscan")){unsigned lo=val(tok[1]),hi=val(tok[2]),a;for(a=lo;a<hi;a+=4)if(c->busRead32(c,a)!=0xC0FFEE11)break;printf("stackscan lowest-touched=%08x free-bytes=%u\\n",a,a-lo);}\n'
              'else if(!strcmp(tok[0],"ptrread")){unsigned a=c->busRead32(c,val(tok[1]))+val(tok[2]),b=n>3?atoi(tok[3]):4;'
              'printf("ptrread %s+%s=0x%08x\\n",tok[1],tok[2],b==1?c->busRead8(c,a):b==2?c->busRead16(c,a):c->busRead32(c,a));}\n' + a2, 1)
open(dst, 'w').write(s)
print('ok')
