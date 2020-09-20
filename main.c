#include <stdio.h>
#include <string.h>
#include <zconf.h>
#include "iLibX.h"

#define MBUFF 500
#define SBUFF 100
#define XLBUFF 1200

int main(int argc, char *argv[]) {
    //basic connection information definitions
    const char *deviceip = "127.0.0.1";
    const char *port = "7788";
    const char *passwd = "alpine";

    printf("iShell v0.1 - DuffyAPP_IT\n");

    //initialise device proxy
    char proxy[MBUFF];
    sprintf(proxy,"iproxy %s 44 >/dev/null 2>/dev/null &", port);
    if(macosRunGetExit(proxy)==0){
        if(DEBUG==1){
            printf("enabling write access\n");
        }
        if(argv[1]!=NULL){
            //enable disk write
            if(iosRunGetExit("mount -o rw,union,update /",deviceip,port,passwd)==0){
                if(DEBUG==1){
                    printf("Write acccess enabled\n");
                }
            } else{
                printf("no checkra1n'ed device connected!\n");
                return 1;
            }

            if(strcmp(argv[1],"-send")==0){
                //check input file is present
                if(argv[2]!=NULL){
                    //check input file is accesible
                    if(access(argv[2],F_OK) == 0){
                        printf("File exists\n");
                        //check dest folder is present
                        if(argv[3]!=NULL){
                            if(iosSendFile(argv[2],argv[3],deviceip,port,passwd)==0){
                                printf("Sent %s!", argv[2]);
                            } else{
                                printf("error sending file :-(");
                                return 1;
                            }
                        } else{
                            printf("Invalid Destination Folder\n");
                            return 1;
                        }
                    } else {
                        printf("Check input file is accessible\n");
                        return 1;
                    }
                } else{
                    printf("you didn't supply a file\n");
                    return 1;
                }
            }

            if(strcmp(argv[1],"-fetch")==0){
                //input remote file path
                if(argv[2]!=NULL){
                    if(iosRecFile(argv[2],".",0,deviceip,port,passwd)==0){
                        printf("File Transmitted! Check The Current Directory!\n");
                    } else{
                        printf("File NOT Transmitted! Does The File Exist?\n");
                        return 1;
                    }
                } else{
                    printf("You Didn't Supply The Path!\n");
                    return 1;
                }
            }

            if(strcmp(argv[1],"-mkdir")==0){
                if(argv[2]!=NULL){
                    if(DEBUG==1){
                        printf("creating directory\n");
                    }
                    if(iosMakeDirectory(argv[2],deviceip,port,passwd)==0){
                        printf("Directory '%s' Created!\n",argv[2]);
                    } else{
                        printf("Error Creating Directory!\n");
                        return 1;
                    }
                } else{
                    printf("You didn't supply the directory to create!\n");
                    return 1;
                }
            }

            if(strcmp(argv[1],"-ecid")==0){
                printf("ECID: %s",iosFetchECID());
            }

            if(strcmp(argv[1],"-shsh")==0){
                printf("exec\n");
                char ptype[SBUFF];
                sprintf(ptype,"%s",strtok(iosFetchPType(),"\n"));

                char bconf[SBUFF];
                sprintf(bconf,"%s",strtok(iosFetchBoardConfig(),"\n"));

                char ecid[SBUFF];
                sprintf(ecid,"%s",strtok(iosFetchECID(),"\n"));

                iosFetchSHSH(ptype,ecid,bconf);
            }

            if(strcmp(argv[1],"-c")==0){
                char comm[XLBUFF];
                for(int i=2;i<argc;i++){
                    sprintf(comm,"%s %s",comm,argv[i]);
                }
//                sprintf(comm,"%s",strtok(comm,"\n"));
//                printf("com:\n%s",comm);
                if(argv[2]!=NULL){
                    printf("%s",iosRunComm(comm,deviceip,port,passwd));
                }
            }

        } else{
            printf("./ishell\n\t-send\tlocalfile.txt /myfiles/\n\t-fetch\t/myfiles/remote.txt nowlocal.txt\n\t-mkdir\t/myfiles/newdirectory\n");
            printf("\t-ecid\t(no args required)\n\t-shsh\t(no args required)\n\t-c\tCOMMAND\n");
        }
    }

    //kill iproxy at end of execution
    macosRunComm("pkill iProxy");
    macosRunComm("echo hello");
    return 0;
}
