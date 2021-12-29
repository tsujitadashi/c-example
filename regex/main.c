#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

static char* API_GW_HOSTNAME_PATTERN = "[.]execute-api[.][a-z0-9-]+[.]amazonaws[.]com$";
static char* API_GW_COMMON_NAME = "*.execute-api.ap-northeast-1.amazonaws.com";

void errorExit(int errorCode, char* errorMessage) {
    printf("%s\n", errorMessage);
    exit(errorCode);
}

int main() {
  regex_t re;
  regmatch_t pmatch[1];
  regoff_t off, len;
  const int errBufSize = 128;
  char errBuf[errBufSize] = {0};

  char* str = API_GW_COMMON_NAME;
  char* pattern = API_GW_HOSTNAME_PATTERN;

  printf("String = %s\n", str);
  printf("Pattern = %s\n", pattern);
  printf("Matches:\n");

  int rc = regcomp(&re, pattern, REG_EXTENDED | REG_ICASE | REG_NEWLINE );
  if (rc) {
    regerror(rc, &re, errBuf, errBufSize);
    errorExit(rc, errBuf);
  }

  rc = regexec(&re, str, ARRAY_SIZE(pmatch), pmatch, 0);
  if (rc) {
    regerror(rc, &re, errBuf, errBufSize);
    errorExit(rc, errBuf);
  }

  off = pmatch[0].rm_so + (str - API_GW_HOSTNAME_PATTERN);
  len = pmatch[0].rm_eo - pmatch[0].rm_so;
  printf("offset = %jd; length = %jd\n", (intmax_t) off, (intmax_t) len);
  printf("substring = \"%.*s\"\n", len, str + pmatch[0].rm_so);
  str += pmatch[0].rm_eo;
}
