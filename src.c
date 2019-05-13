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

  //시간 측정 시작
  start = clock();

  //argv[1] 파일명으로 읽기 파일 오픈
  FILE *fpr = fopen(argv[1], "r");
  //argv[1] 파일명에 _output 을 추가하여 쓰기 파일 오픈
  tok_char = strtok(argv[1], ".");
  file_out = strcat(tok_char, "_output.txt");
  FILE *fpw = fopen(file_out, "w");

  //파일 읽기에 성공 시 실행
  if(fpr!=NULL)
  {
    //한 줄씩 읽어 buffer에 저장하여 사용
    while(fgets(buffer, SIZE_BUFFER, fpr))
    {
      //buffer의 내용을 "공백" 기준으로 자르고
      //성명(좌측) 을 tok_char 에 저장
      tok_char = strtok(buffer, " ");
      //주민등록번호(우측)을 tok_num 에 저장
      tok_num = strtok(NULL, " ");
      strncpy(plain, tok_num, 14);

      //주민등록번호(우측)을 openssl/sha 를 이용하여 해쉬화하여 mdString에 저장
      SHA256((unsigned char*)&plain, strlen(plain), (unsigned char*)&digest);
      char mdString[SHA256_DIGEST_LENGTH*2*1];
      for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
      {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
      }

      //디버깅용 프롬프트 출력
      //printf("Name : %s | Plain : %s | Length : %d\n",tok_char, plain, strlen(plain));
      //printf("Hash : %s\n",mdString);
      //쓰기 파일에 출력
      fputs(tok_char, fpw); fputs(" ", fpw);
      fputs(mdString, fpw); fputs("\n", fpw);
    }

    fclose(fpr);
    fclose(fpw);
  }
  //시간 측정 끝
  end = clock();
  result_clock = (double)(end - start)/1000000;
  //시간 측정 결과 출력
  printf("%f\n", result_clock);

  return 0;
}
