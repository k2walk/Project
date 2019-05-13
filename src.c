#include <stdio.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h> //openssl 3.0.0-dev

#define SIZE_BUFFER 1024

int main(int argc, char *argv[])
{
  char buffer[SIZE_BUFFER];
  unsigned char digest[SHA256_DIGEST_LENGTH];
  char *tok_char;
  char *tok_num;
  char plain[14];
  char *file_out;
  clock_t start, end;
  double result_clock;

  //�ð� ���� ����
  start = clock();

  //argv[1] ���ϸ����� �б� ���� ����
  FILE *fpr = fopen(argv[1], "r");
  //argv[1] ���ϸ� _output �� �߰��Ͽ� ���� ���� ����
  tok_char = strtok(argv[1], ".");
  file_out = strcat(tok_char, "_output.txt");
  FILE *fpw = fopen(file_out, "w");

  //���� �б⿡ ���� �� ����
  if(fpr!=NULL)
  {
    //�� �پ� �о� buffer�� �����Ͽ� ���
    while(fgets(buffer, SIZE_BUFFER, fpr))
    {
      //buffer�� ������ "����" �������� �ڸ���
      //����(����) �� tok_char �� ����
      tok_char = strtok(buffer, " ");
      //�ֹε�Ϲ�ȣ(����)�� tok_num �� ����
      tok_num = strtok(NULL, " ");
      strncpy(plain, tok_num, 14);

      //�ֹε�Ϲ�ȣ(����)�� openssl/sha �� �̿��Ͽ� �ؽ�ȭ�Ͽ� mdString�� ����
      SHA256((unsigned char*)&plain, strlen(plain), (unsigned char*)&digest);
      char mdString[SHA256_DIGEST_LENGTH*2*1];
      for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
      {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
      }

      //������ ������Ʈ ���
      //printf("Name : %s | Plain : %s | Length : %d\n",tok_char, plain, strlen(plain));
      //printf("Hash : %s\n",mdString);
      //���� ���Ͽ� ���
      fputs(tok_char, fpw); fputs(" ", fpw);
      fputs(mdString, fpw); fputs("\n", fpw);
    }

    fclose(fpr);
    fclose(fpw);
  }
  //�ð� ���� ��
  end = clock();
  result_clock = (double)(end - start)/1000000;
  //�ð� ���� ��� ���
  printf("%f\n", result_clock);

  return 0;
}
