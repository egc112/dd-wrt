#include <stdio.h>
#include <malloc.h>
#include <string.h>


int main(int argc, char *argv[])
{
FILE *in,*out;
in=fopen(argv[1],"rb");
out=fopen(argv[2],"wb");
fseek(in,0,SEEK_END);
size_t len = ftell(in);
rewind(in);
char *mem=malloc(len + (1024*1024));
memset(mem, 0, len + (1024*1024));
fread(mem,len,1,in);
size_t i;
size_t rlen;
for (i=0;i<len;i++) {
    if (mem[i]!=0)
	rlen = i;
}
//rlen = 819200*512;
rlen += 1024*1024;
rlen +=511;
rlen /=512;
rlen *=512;
fwrite(mem,rlen,1,out);
fclose(in);
fclose(out);

}
