#include <stdio.h>
#include <string.h>
#include <windows.h>

struct w
{
    char in[100];
};

char endwords[100]="再见";
char ini[100]="初始化";
char cha[100]="修改";
char clean[100]="清屏";
void initialize();

void initi()//读取初始化词汇
{
    FILE *init=NULL;
    init=fopen("init.txt","r");
    fscanf(init,"%s\n%s\n%s\n%s",endwords,ini,cha,clean);
    fclose(init);
}

void learning()//学习模式
{
    char learning[100];
    char feedback[100];
    printf("当您说：");
    scanf("%s",&learning);
    printf("我应当说：");
    scanf("%s",&feedback);

    FILE *words=NULL;
    words=fopen("words.txt","a");
    while(feof(words)==0)
    {
        fprintf(words,"\n%s\n%s",learning,feedback);
        fclose(words);
        printf("学习完毕！\n\n");
        return ;
    }
}

char understand(char input[])//理解模式
{
    char search[100];
    FILE *words=NULL;
    words=fopen("words.txt","r");
    if(words==NULL)
    {
        MessageBox(NULL,"   初始文件丢失！请重新下载文件！   ","错误！！！",MB_OK);
        exit (0);
    }

    while(feof(words)==0)
    {
        fscanf(words,"%s\n",&search);

        if(strcmp(search,input)==0)
        {
            char feedback[100];
            fscanf(words,"%s",&feedback);
            printf("%s\n",feedback);
            return;
        }
    }

    int a;
    printf("抱歉，你太聪明啦~我不能理解。\n");
    printf("需要进入学习流程吗？(需要请输入1)\n");
    scanf("%d",&a);
    if(a==1)
    {
        learning();
    }

    fclose(words);
}

void changeM()//修改模式
{
    struct w a[1000];//词库大小可变
    struct w search;
    struct w change;

    FILE *words=NULL;
    words=fopen("words.txt","r");
    if(words==NULL)
    {
        MessageBox(NULL,"   初始文件丢失！请重新下载文件！   ","错误！！！",MB_OK);
        exit (0);
    }

    int i=0,t=0;
    while(feof(words)==0)
    {
        fscanf(words,"%s\n",&a[i].in);
        i++;
        t=i;
    }

 a3:printf("需要修改什么记忆？\n");
    getchar();
    gets(search.in);

    i=0;
    int flag=0;
    while(i<=t)
    {
        if(strcmp(search.in,a[i].in)==0)
        {
            printf("原记忆：%s\n",a[i+1].in);
            printf("修改后记忆：");
            gets(change.in);
            strcpy(a[i+1].in,change.in);
            printf("修改成功！\n");
            flag=1;
            break;
        }
        i++;
    }

    if(flag==0)
    {
        int n;
        printf("记忆不存在，请重新输入。(不需要修改请输入1回到聊天界面，需要修改请输入2)\n");
        scanf("%d",&n);
        if(n == 1)
        {
           fclose(words);
           return;
        }
        else
        {
            goto a3;
        }
    }

    words=fopen("words.txt","w");
    i=0;
    while(i<=t)
    {
        fprintf(words,"%s\n",a[i].in);
        i++;
    }
    fclose(words);

}

void check(char input[])
{
    char search[100];
    FILE *words=NULL;
    words=fopen("words.txt","r");
    if(words==NULL)
    {
        MessageBox(NULL,"   初始文件丢失！请重新下载文件！   ","错误！！！",MB_OK);
        exit (0);
    }

    while(feof(words)==0)
    {
        fscanf(words,"%s\n",&search);

        if(strcmp(search,input)==0)
        {
            printf("与已有词汇冲突请重新输入：");
            initialize();
        }
    }
}


void initialize()//初始化设定
{
    FILE *save;
    save=fopen("save.txt","w");
    int a=1;
    fprintf(save,"%d\n",a);
    fclose(save);

    int b;
 a1:printf("是否进入初始化设定？(需要请输入1，不需要请输入2，如需再次进入初始化设定请输入“初始化”)\n");
    scanf("%d",&b);
    getchar();

    switch(b)
    {
        case 1:
               {
                printf("当您输入什么时结束本聊天机器人进程：（初始设定为：再见）\n设定：");
                scanf("%s",&endwords);
                check(endwords);

                printf("当您输入什么时进入初始化进程：（初始设定为：初始化）\n设定：");
                scanf("%s",&ini);
                check(ini);

                printf("当您输入什么时进入修改进程：（初始设定为：修改）\n设定：");
                scanf("%s",&cha);
                check(cha);

                printf("当您输入什么时清屏：（初始设定为：清屏）\n设定：");
                scanf("%s",&clean);
                check(clean);

                FILE *init=NULL;
                init=fopen("init.txt","w");
                fprintf(init,"%s\n%s\n%s\n%s",endwords,ini,cha,clean);
                fclose(init);

                printf("设定完毕！\n");
                return;
               }
        case 2:return;
        default:goto a1;break;
    }
    return;
}

void main()
{
    char input[100];

    //判断是否第一次打开
    int s;
    FILE *save=NULL;
    save=fopen("save.txt","r");
    if(save==NULL)
    {
        printf("无法找到！");
        return;
    }

    fscanf(save,"%d",&s);
    if(s==0)
    {
       initialize();
    }
    fclose(save);


    printf("您好，我是您的定制朋友，请问有什么需要吗？\n\n");
    initi();

    while(1)
    {
     a2:printf("您说：");
        scanf("%s",&input);

        if(strcmp(input,endwords)==0)
        {
            printf("与您聊天十分开心~\n");
            break;
        }
        if(strcmp(input,ini)==0)
        {
            initialize();
            goto a2;
        }
        if(strcmp(input,cha)==0)
        {
            changeM();
            goto a2;
        }
        if(strcmp(input,clean)==0)
        {
            system("cls");
            goto a2;
        }
        understand(input);
    }
}
