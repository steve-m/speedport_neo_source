#ifndef __3G_UTILS__
#define __3G_UTILS__


int atcmd_tool(char *dev, char *cmd, char *output, int output_len, int only_oneline);
int atcmd_tool_reader(char *dev, char *output, int output_len, int only_oneline);

int atcmd_tool_fd(int fd, char *dev, char *cmd, char *output, int output_len, int only_oneline);
int atcmd_tool_reader_fd(int fd, char *dev, char *output, int output_len, int only_oneline);



#endif

