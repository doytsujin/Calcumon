#ifndef dialog_include_file
#define dialog_include_file

#ifdef __cplusplus
extern "C" {
#endif

extern void ShowText(const char* text);
extern bool AskBoolText(const char* text);
extern uint8_t AskNumText(const char* text, const uint8_t _max);
extern char* AskText();

#ifdef __cplusplus
}
#endif

#endif
