/**********************************************************************************
*Filename:     kjx_reduce_string.c
*
*Description:  
*
*Author:        caoweijie
*
*Datetime:    2014/08/26
*
***********************************************************************************/
#if defined(__KJX_FUN__)
#include "kjx_include.h"

#ifndef NULL
 #define NULL   (0)
#endif

char* restring=NULL;
char* dstring1=NULL;
char* dstring2=NULL;
char* dstring3=NULL;
char* outstring=NULL;
char* outstring1=NULL;

/*========================================================
==========================================================
��������:char* kjx_check_file_data(char* filename,char* headstr,char*datastr,char* endstr,int index)
ʵ�ֹ���:���ҡ��޸�����
����:filebuffer  �ļ�����
            headstr    ����ͷ
            datastr    д������
            endstr      ����β
            index       ��дģʽ   1Ϊ�� /2Ϊд
            handle  �ļ�����
����:���ݡ�0��дʧ�ܡ�1д��ɹ�
==========================================================
========================================================*/
char* kjx_check_file_data(char*filebuffer,int bufflen,char* headstr,char*datastr,char* endstr,int index,FS_HANDLE handle)
{      
	char* restring=NULL;
	char* strhead=NULL;
	char* strend=NULL;
	char* tem1=NULL;
	char* tem2=NULL;
	char* tem3=NULL;
	int readsize;
	int i=0,j=0,strleng=0,datalen=0,begleng=0,lastleng=0,input=0;

	dstring1=NULL;
	dstring2=NULL;
	dstring3=NULL;

	switch(index)
	{
	case 1://��ȡ
		if(!(strlen((const char *)filebuffer)))
		{
			//������
			restring="-1";
			break;
		}

		strhead=(char*)strstr((const char *)filebuffer, (const char *)headstr);
		if(strhead)
		{
			//�����ļ�ͷ
			strend=(char*)strstr((const char *)filebuffer, (const char *)endstr);
			if(strend)
			{
				//�����ļ�β
				datalen=strend-strhead-(strlen((const char *)headstr));//ʵ�����ݳ���
				if(dstring1==NULL)
				{

					dstring1 = (char*) OslMalloc(datalen+100);
					tem1=dstring1;
				}

				memset(dstring1, 0, strlen((const char *)dstring1));
				memcpy((char*)dstring1, (const char *)strhead+(strlen((const char *)headstr)), datalen);//��ȡʵ������
				dstring1[datalen]='\0';

				restring=(char*)dstring1;
				if(dstring1!=NULL)
				{
					OslMfree(tem1);
					dstring1=NULL;
					tem1=NULL;
				} 
			}
			else
			{
				//�Ҳ����ļ�β�����ݴ���
				restring="-1";
			}
		}
		else
		{
			//û����Ҫ������
			restring="-1";
		}
		break;

	case 2://д��
		if(!filebuffer)
		{
			//û�У���ֱ���������
			FS_Write(handle,headstr,strlen((const char *)headstr),(UINT*)&readsize);
			FS_Write(handle,datastr,strlen((const char *)datastr),(UINT*)&readsize);
			FS_Write(handle,endstr,strlen((const char *)endstr),(UINT*)&readsize);

			if(readsize)
				restring="1";
			else
				restring="-1";
			
			break;
		}

		if(!bufflen)
		{
			//������
			restring="-1";
			break;
		}

		strhead=(char*)strstr((const char *)filebuffer, (const char *)headstr);
		if(strhead)
		{
			//�����ļ�ͷ�������ļ�ͷ�����滻����
			strend=(char*)strstr((const char *)filebuffer, (const char *)endstr);
			if(strend)
			{
				//�����ļ�β
				begleng=strhead-filebuffer;//�滻����ǰ�����ݳ���
				if(begleng>0)
				{
					if(dstring2==NULL)
					{    
					dstring2 = (char*) OslMalloc(begleng+100);
					tem2=dstring2;
					}

					memset(dstring2, 0, strlen((const char *)dstring2));
					memcpy((char*)dstring2, (const char *)filebuffer, begleng);//�滻����ǰ������
					dstring2[begleng]='\0';

					FS_Write(handle,dstring2,begleng,(UINT*)&readsize);
					if(dstring2!=NULL)
					{
						OslMfree(tem2);
						dstring2=NULL;
						tem2=NULL;
					}

					if(readsize)
						restring="1";
					else
						restring="-1";
				}

				//�滻���ݺ������� 
				if(dstring3==NULL)
				{
					dstring3 = (char*) OslMalloc(strlen((const char *)strend+(strlen((const char *)endstr)))+100);
					tem3=dstring3;
				}

				memset(dstring3, 0, strlen((const char *)dstring3));
				memcpy((char*)dstring3, (const char *)strend+(strlen((const char *)endstr)), strlen((const char *)strend+(strlen((const char *)endstr))));
				dstring3[strlen((const char *)strend+(strlen((const char *)endstr)))]='\0';

				FS_Write(handle,dstring3,strlen((const char *)strend+(strlen((const char *)endstr))),(UINT*)&readsize);
				if(dstring3!=NULL)
				{
					OslMfree(tem3);
					dstring3=NULL;
					tem3=NULL;
				}
	
				if(readsize)
					restring="1";
				else
					restring="-1";

				FS_Write(handle,headstr,strlen((const char *)headstr),(UINT*)&readsize);
				FS_Write(handle,datastr,strlen((const char *)datastr),(UINT*)&readsize);
				FS_Write(handle,endstr,strlen((const char *)endstr),(UINT*)&readsize);

				if(readsize)
					restring="1";
				else
					restring="-1";

			}
			else
			{//�Ҳ����ļ�β�����ݴ��󣬲����������ͬ�ļ�ͷ����
				restring="-1";
			}
		}
		else
		{
			//û�У���ֱ���������
			FS_Write(handle,filebuffer,strlen((const char *)filebuffer),(UINT*)&readsize);
			FS_Write(handle,headstr,strlen((const char *)headstr),(UINT*)&readsize);
			FS_Write(handle,datastr,strlen((const char *)datastr),(UINT*)&readsize);
			FS_Write(handle,endstr,strlen((const char *)endstr),(UINT*)&readsize);

			if(readsize)
				restring="1";
			else
				restring="-1";
		}
		break;

	default: 
		restring="-1";
		break;
	}

	return (char*)restring;
}


/*========================================================
==========================================================
��������:int kjx_get_parameter_number(char* stringbuffer,char* header,char* ender,char* sign,int MaxNum)
ʵ�ֹ���:���������ַ����ͱ�ʶ��������������ĸ���
����:stringbuffer  �ַ���
            sign            ��ʶ��
            header  ����ͷ
            ender    ����β
            MaxNum  ���������������������ô��ڲ���������ֵ
����:��������
==========================================================
========================================================*/
int kjx_get_parameter_number(char* stringbuffer,char* header,char* ender,char* sign,int MaxNum)
{
	int i;
	char* string=NULL;
	char* instring=NULL;

	//��ȡָ��ͷ��β���ַ���
	instring=(char*)kjx_check_file_data((char*)stringbuffer,NULL,header,NULL,ender,1,NULL);

	for(i=0;i<MaxNum;i++)
	{
		string=(char*)strstr((const char *)instring, (const char *)sign);
		if(!string)
		{
			break;
		}

		instring=string+strlen((const char *)sign);
	}

	//i Ϊ��ʶ�����ֵĴ�������Ҫ+1���ز����ĸ���
	return i+1;
}

/*========================================================
==========================================================
��������:char* kjx_get_parameter_string(char* stringbuffer,char* header,char* ender,char* sign,int index)
ʵ�ֹ���:����δ�ֽ��ַ����У�ָ���������ַ���
����:stringbuffer  �ַ���
            sign            ��ʶ��,���û�������NULL
            header  ����ͷ
            ender    ����β
            index  ������������1��ʼ����
����:��ǰ������ָ��Ĳ���
==========================================================
========================================================*/
char* kjx_get_parameter_string(char* stringbuffer,char* header,char* ender,char* sign,int index)
{
	int i,strnum,in_total;
	char* string=NULL;
	char* instring=NULL;
	char* temGetstring=NULL;
	S8 prin[100];

	in_total=0;
	//��ȡָ��ͷ��β���ַ���
	instring=(char*)kjx_check_file_data((char*)stringbuffer,NULL,header,NULL,ender,1,NULL);

	if(sign==NULL)
	{
		return (char*)instring;
	}

	for(i=0;i<index;i++)
	{	   
		string=(char*)strstr((const char *)instring, (const char *)sign);
		strnum=string-instring;
		if((!string)||(strnum<0))
		{
			in_total++;
			if(in_total==1)
				return (char *)instring;
			else if(in_total>1)
				return NULL;
		}

		if(restring!=NULL)
		{
			OslMfree(restring);
			restring=NULL;
		}

		if(restring==NULL)
		{
			restring = (char*) OslMalloc(strnum+100);
		}

		memset(restring, 0, strlen((const char *)restring));
		memcpy((char*)restring, (const char *)instring, strnum);
		restring[strnum]='\0';

		instring=string+strlen((const char *)sign);
	}

	return (char*)restring;
}

/*========================================================
==========================================================
��������:char* kjx_get_parameter_string_extern(char* stringbuffer,char* header,char* ender,char* subHeader,char* subEnder,int index)
ʵ�ֹ���:����δ�ֽ��ַ����У�ָ���������ַ���
����:stringbuffer  �ַ���
            header  ����ͷ
            ender    ����β
            subHeader  ������ͷ
            subEnder    ������β
            index  ������������1��ʼ����
����:��ǰ������ָ��Ĳ���
==========================================================
========================================================*/
char* kjx_get_parameter_string_extern(char* stringbuffer,char* header,char* ender,char* subHeader,char* subEnder,int index)
{
	int i,strnum,in_total;
	char* string=NULL;
	char* instring=NULL;
	char* temGetstring=NULL;

	if(restring!=NULL)
	{
		OslMfree(restring);
		restring=NULL;
	}

	if(restring==NULL)
	{
		restring = (char*) OslMalloc(512);
	}

	in_total=0;
	//��ȡָ��ͷ��β���ַ���
	instring=(char*)kjx_check_file_data((char*)stringbuffer,NULL,header,NULL,ender,1,NULL);

	for(i=0;i<index;i++)
	{	
		string=(char*)strstr((const char *)instring, (const char *)subHeader);
		if(instring)
		{
			instring += strlen((const char *)subHeader);
		}

		string=(char*)strstr((const char *)instring, (const char *)subEnder);
		strnum=string-instring;
		if((!string)||(strnum<0))
		{
			in_total++;
			if(in_total==1)
				return (char *)instring;
			else if(in_total>1)
				return NULL;
		}

		memset(restring, 0, strlen((const char *)restring));
		memcpy((char*)restring, (const char *)instring, strnum);
		restring[strnum]='\0';

		instring=instring+strnum+strlen((const char *)subEnder);
	}

	return (char*)restring;
}
/*========================================================
==========================================================
��������:char* kjx_get_parameter_string_only_in_buffer(char* stringbuffer,char* sign,int index)
ʵ�ֹ���:����δ�ֽ��ַ����У�ָ���������ַ���(���ļ�ͷ��β)
����:stringbuffer  �ַ���
            sign            ��ʶ��,���û�������NULL
            index  ������������1��ʼ����
����:��ǰ������ָ��Ĳ���
==========================================================
========================================================*/
char* kjx_get_parameter_string_only_in_buffer(char* stringbuffer,char* sign,int index)
{
	int i,strnum,in_total;
	char* string=NULL;
	char* instring=NULL;
	char* temGetstring=NULL;  

	in_total=0;
	instring=stringbuffer;
	if(strlen(sign)==0)
	{
		return (char*)instring;
	}

	for(i=0;i<index;i++)
	{
		U32 len;

		len = strlen((const char *)instring);
		string=NULL;
		string=(char*)strstr((const char *)instring, (const char *)sign);
		strnum=string-instring;
		if((!string)||(strnum<0))
		{
			in_total++;
			if(in_total==1)
			{
				if(outstring1 != NULL)
				{
					media_free_ext_buffer(MOD_MMI, (void**)&outstring1);
					outstring1 = NULL;
				}

				if(outstring1 == NULL)
				{
					media_get_ext_buffer(MOD_MMI, (void **)&outstring1, len+1);
					if(outstring1 == NULL)
						return;
				}
				
				memset(outstring1, 0, len+1);
				strncpy((char*)outstring1, (const char *)instring, len);
				return (char *)outstring1;
			}
			else if(in_total>1)
			{
				return NULL;
			}
		}

		if(outstring1!=NULL)
		{
			media_free_ext_buffer(MOD_MMI, (void**)&outstring1);
			outstring1 = NULL;
		}

		if(outstring1==NULL)
		{   
			media_get_ext_buffer(MOD_MMI, (void **)&outstring1, strnum+1);
			if(outstring1 == NULL)
				return;
		}
		memset(outstring1, 0, strnum+1);
		memcpy((char*)outstring1, (const char *)instring, strnum);
		instring=string+strlen((const char *)sign);
	}

	return (char*)outstring1;
}

char* kjx_get_parameter_string_only_in_buffer_extern(char* stringbuffer,char* sign,int index)
{
	int i=0,strnum=0,in_total=0;
	char* string=NULL;
	char* instring=NULL;

	in_total=0;
	instring=stringbuffer;
	if(strlen(sign)==0)
	{
		return (char*)instring;
	}

	for(i=0;i<index;i++)
	{
		string=NULL;
		string=(char*)strstr((const char *)instring, (const char *)sign);

		strnum=string-instring;
		if((!string)||(strnum<0))
		{ 
			if(i<index-1)
				return NULL;

			in_total++;
			if(in_total==1)
			{
				if(outstring!=NULL)
				{
					OslMfree(outstring);
					outstring=NULL;
				}

				if(outstring==NULL)
				{   
					outstring = (char*) OslMalloc(128);
				}              
				memset(outstring, 0, 128);
				strncpy((char*)outstring, (const char *)instring, strlen((const char *)instring));
				outstring[strlen((const char *)instring)]='\0';
				return (char *)outstring;
			}
			else if(in_total>1)
			{
				return NULL;
			}
		}

		if(outstring!=NULL)
		{
			OslMfree(outstring);
			outstring=NULL;
		}

		if(outstring==NULL)
		{   
			outstring = (char*) OslMalloc(128);
		}

		memset(outstring, 0, 128);
		memcpy((char*)outstring, (const char *)instring, strnum);
		outstring[strnum]='\0';

		instring=string+strlen((const char *)sign);
	}

	return (char*)outstring;
}

#endif
