#ifndef dialog_include_file
#define dialog_include_file

#ifdef __cplusplus
extern "C" {
#endif

extern void ShowText(const char* text);
extern bool AskBoolText(const char* text);
extern uint8_t AskNumText(const char* text, const uint8_t _max);
extern char* AskText();
extern void InstantPrintHugeText(const char* text, const uint24_t x, const uint8_t y);

#ifdef __cplusplus
}
#endif

#endif
