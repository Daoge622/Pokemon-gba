// Environment acceptance harness: drives mGBA's public core API, never patches ROM data.
#include <mgba/core/core.h>
#include <mgba/core/config.h>
#include <mgba/core/serialize.h>
#include <mgba-util/vfs.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
static void frames(struct mCore *c, int n, unsigned keys) {
    c->setKeys(c, keys);
    while(n-- > 0) c->runFrame(c);
    c->setKeys(c, 0);
}
static void image(struct mCore *c,const char *path) {
    struct VFile *f=VFileOpen(path,O_WRONLY|O_CREAT|O_TRUNC);
    if(!f || !mCoreTakeScreenshotVF(c,f)) { fprintf(stderr,"Screenshot failed\n"); exit(2); }
    f->close(f);
}
int main(int argc,char **argv) {
    if(argc!=4) return 2;
    struct mCore *c=mCoreFind(argv[1]);
    if(!c || !c->init(c)) return 3;
    mCoreInitConfig(c,"environment-check");
    color_t *pixels=calloc(240*160,sizeof(color_t));
    c->setVideoBuffer(c,pixels,240);
    if(!mCoreLoadFile(c,argv[1])) return 4;
    c->reset(c);
    frames(c,1800,0);
    image(c,argv[2]);
    // Upstream debug quickstart: hold Select across frames so sampling cannot miss it.
    for(int i=0;i<4;i++) { frames(c,20,1u<<2); frames(c,100,0); }
    frames(c,600,0);
    image(c,argv[3]);
    struct VFile *f=VFileOpen("/mnt/d/Pokemon gba/artifacts/verification/field.ss0",O_RDWR|O_CREAT|O_TRUNC);
    if(!f || !mCoreSaveStateNamed(c,f,0)) return 5;
    f->close(f);
    char title[17]={0}; c->getGameTitle(c,title);
    printf("mGBA core title=%s frames=%u ROM=%zu bytes\n",title,c->frameCounter(c),c->romSize(c));
    c->unloadROM(c); mCoreConfigDeinit(&c->config); c->deinit(c); free(pixels);
    return 0;
}
