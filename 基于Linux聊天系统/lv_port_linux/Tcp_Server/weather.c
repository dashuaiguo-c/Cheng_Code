#include "tcp_server.h"

bool Send_All_Weather(client_link present_client_node)
{
    pthread_mutex_lock(&present_client_node->p_si->mutex);    //上锁
	int scok_fd=0;
	scok_fd=Cilent_Init();
	if(-1==scok_fd)
	{
		printf("客户端初始化失败\n");
		return false;
	}

	if(-1==Send_Request(scok_fd,present_client_node))
	{
		printf("发送请求失败\n");
		return false;
	}
	char *p=Get_Alaysis_Response(scok_fd);
    if(NULL==p)
	{
		printf("解析头部报文失败\n");
		return false;
	}
    char buf[4096]="\0";
    sprintf(buf,"%s",p);
    write(present_client_node->cli_fd,buf,sizeof(buf));
    pthread_mutex_unlock(&present_client_node->p_si->mutex);    //解锁

    //发送ok让客户端跳出while
    if(write(present_client_node->cli_fd,FINISH,strlen(FINISH)) == -1)
    {
        perror("write ...");
        return false;
    }
	close(scok_fd);
	return true;
}


int Cilent_Init()
{
	//通过天气TCP服务器域名 求出 外网IP
	struct hostent * he =  gethostbyname("restapi.amap.com");
	if(he == (struct hostent *)NULL)
	{
		perror("gethostnyname ...");
		return -1;
	}
	printf("该服务器IP为:%s\n",inet_ntoa(*(struct in_addr *)he->h_addr_list[0]));

	//创建客户端套接字
	int sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd == -1)
	{
		perror("socket ...");
		return -1;
	}

	//连接天气TCP服务器
	struct sockaddr_in ser_inf;
	memset(&ser_inf,0,sizeof(ser_inf));
	ser_inf.sin_family 		= AF_INET;
	ser_inf.sin_port  		= htons(80);
	ser_inf.sin_addr.s_addr = *((uint32_t *)he->h_addr_list[0]);
	// struct in_addr addr;
	// memcpy(&addr, he->h_addr_list[0], sizeof(struct in_addr));
	// ser_inf.sin_addr = addr;

	if(connect(sock_fd,(struct sockaddr *)&ser_inf,sizeof(ser_inf)) == -1)
	{
		perror("connect ...");
		return -1;
	}
	else
	{
		printf("连接服务器成功！\n");
	}

	return sock_fd;
}

int Send_Request(int sock_fd,client_link present_client_node)
{
	//发送请求
	char address[17]="\0";
    printf("等待客户端选择要查询的城市\n");
    read(present_client_node->cli_fd,address,sizeof(address));
	char request[1024]={0};
	sprintf(request,"GET /v3/weather/weatherInfo?city=%s&key=8dd2dde0b15106b70caab10a6b8a7576&extensions=all HTTP/1.1\r\nHost:restapi.amap.com\r\n\r\n",address);
	int ret=write(sock_fd,request,strlen(request));
	if(-1==ret)
	{
		perror("发送请求失败");
		return -1;
	}
    printf("服务器请求发送完毕\n");
	return 0;
}

char *Get_Alaysis_Response(int sock_fd)
{
	//接收服务器报文
	char buf[1024*4]={0};
	memset(buf,0,sizeof(buf));
    while(1)
    {
        ssize_t ret=read(sock_fd,buf,4096);
        if(ret==-1)
        {
            perror("获取服务器报文失败");
			return NULL;
        }
		else if(0==ret)
		{
			break;
		}
    }

	// printf("%s\n",buf);
	char *retcode = buf+strlen("HTTP/x.x ");  //状态码
	switch(atoi(retcode))
    {
        case 200 ... 299 : printf("查询成功!\n");break;
        case 400 ... 499 : printf("客户端有误!\n");return NULL;
        case 500 ... 599 : printf("服务器有误!\n");return NULL;
    }

	int response_package_size;
    char * obj_p= NULL;
	if(obj_p = strstr(buf,"Content-Length: "))
	{
		response_package_size = atoi(obj_p+strlen("Content-Length: "));
		printf("响应包体大小：%d\n",response_package_size);
	}

	char *p=strstr(buf,"\r\n\r\n");
	// printf("%s\n",p+2);

	return p+4;
}
