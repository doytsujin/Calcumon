#ifndef dialog_include_file
#define dialog_include_file

#ifdef __cplusplus
extern "C" {
#endif

extern void ShowText(char* text);
extern bool AskBoolText(char* text);
extern uint8_t AskNumText(char* text);

#ifdef __cplusplus
}
#endif

#endif
