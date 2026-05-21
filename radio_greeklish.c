#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// ΤΟΠΟΘΕΤΗΣΤΕ ΤΗΝ ΣΩΣΤΗ ΔΙΑΔΡΟΜΗ ΤΩΝ ΔΙΚΩΝ ΣΑΣ ΑΡΧΕΙΩΝ:
const char* INPUT_FILE = "C:\\Path\\To\\Your\\Player_Output.txt";
const char* OUTPUT_FILE = "C:\\Path\\To\\Your\\Broadcaster_Input.txt";



// Αναγνωριστικά
#define ID_TIMER 1
#define ID_LABEL_TITLE 101 // ID για τον τίτλο "ΤΩΡΑ ΠΑΙΖΕΙ:"
#define ID_LABEL_SONG  102 // ID για το όνομα του τραγουδιού

HWND hLabelTitle, hLabelSong;
HFONT hFontTitle, hFontSong;
HBRUSH hBackBrush;
char last_written_content[4096] = {0};

typedef struct { const char* grk; const char* lat; } Rule;

// Λεξικό
Rule dict[] = {
    {"\xCE\x9F\xCE\xA5", "OU"}, {"\xCE\x9F\xCF\x85", "Ou"}, {"\xCE\xBF\xCF\x85", "ou"},
    {"\xCE\x91\xCE\xA5", "AU"}, {"\xCE\x91\xCF\x85", "Au"}, {"\xCE\xB1\xCF\x85", "au"},
    {"\xCE\x95\xCE\xA5", "EU"}, {"\xCE\x95\xCF\x85", "Eu"}, {"\xCE\xB5\xCF\x85", "eu"},
    {"\xCE\x91\xCE\x99", "AI"}, {"\xCE\x91\xCE\xB9", "Ai"}, {"\xCE\xB1\xCE\xB9", "ai"},
    {"\xCE\x95\xCE\x99", "EI"}, {"\xCE\x95\xCE\xB9", "Ei"}, {"\xCE\xB5\xCE\xB9", "ei"},
    {"\xCE\x9F\xCE\x99", "OI"}, {"\xCE\x9F\xCE\xB9", "Oi"}, {"\xCE\xBF\xCE\xB9", "oi"},
    {"\xCE\x9C\xCE\xA0", "MP"}, {"\xCE\x9C\xCF\x80", "Mp"}, {"\xCE\xBC\xCF\x80", "mp"},
    {"\xCE\x9D\xCE\xA4", "NT"}, {"\xCE\x9D\xCF\x84", "Nt"}, {"\xCE\xBD\xCF\x84", "nt"},
    {"\xCE\x93\xCE\x9A", "GK"}, {"\xCE\x93\xCE\xBA", "Gk"}, {"\xCE\xB3\xCE\xBA", "gk"},
    {"\xCE\x93\xCE\x93", "GG"}, {"\xCE\x93\xCE\xB3", "Gg"}, {"\xCE\xB3\xCE\xB3", "gg"},
    {"\xCE\xA4\xCE\xA3", "TS"}, {"\xCE\xA4\xCF\x83", "Ts"}, {"\xCF\x84\xCF\x83", "ts"},
    {"\xCE\xA4\xCE\x96", "TZ"}, {"\xCE\xA4\xCE\xB6", "Tz"}, {"\xCF\x84\xCE\xB6", "tz"},
    {"\xCE\x86", "A"}, {"\xCE\xAC", "a"}, {"\xCE\x88", "E"}, {"\xCE\xAD", "e"},
    {"\xCE\x89", "I"}, {"\xCE\xAE", "i"}, {"\xCE\x8A", "I"}, {"\xCE\xAF", "i"},
    {"\xCE\xAA", "I"}, {"\xCF\x8A", "i"}, {"\xCE\x90", "i"},
    {"\xCE\x8C", "O"}, {"\xCF\x8C", "o"}, {"\xCE\x8E", "Y"}, {"\xCF\x8D", "y"},
    {"\xCE\xAB", "Y"}, {"\xCF\x8B", "y"}, {"\xCE\xB0", "y"}, {"\xCE\x8F", "O"}, {"\xCF\x8E", "o"},
    {"\xCE\x91", "A"}, {"\xCE\xB1", "a"}, {"\xCE\x92", "V"}, {"\xCE\xB2", "v"},
    {"\xCE\x93", "G"}, {"\xCE\xB3", "g"}, {"\xCE\x94", "D"}, {"\xCE\xB4", "d"},
    {"\xCE\x95", "E"}, {"\xCE\xB5", "e"}, {"\xCE\x96", "Z"}, {"\xCE\xB6", "z"},
    {"\xCE\x97", "I"}, {"\xCE\xB7", "i"}, {"\xCE\x98", "Th"}, {"\xCE\xB8", "th"},
    {"\xCE\x99", "I"}, {"\xCE\xB9", "i"}, {"\xCE\x9A", "K"}, {"\xCE\xBA", "k"},
    {"\xCE\x9B", "L"}, {"\xCE\xBB", "l"}, {"\xCE\x9C", "M"}, {"\xCE\xBC", "m"},
    {"\xCE\x9D", "N"}, {"\xCE\xBD", "n"}, {"\xCE\x9E", "X"}, {"\xCE\xBE", "x"},
    {"\xCE\x9F", "O"}, {"\xCE\xBF", "o"}, {"\xCE\xA0", "P"}, {"\xCF\x80", "p"},
    {"\xCE\xA1", "R"}, {"\xCF\x81", "r"}, {"\xCE\xA3", "S"}, {"\xCF\x83", "s"}, {"\xCF\x82", "s"},
    {"\xCE\xA4", "T"}, {"\xCF\x84", "t"}, {"\xCE\xA5", "Y"}, {"\xCF\x85", "y"},
    {"\xCE\xA6", "F"}, {"\xCF\x86", "f"}, {"\xCE\xA7", "Ch"}, {"\xCF\x87", "ch"},
    {"\xCE\xA8", "Ps"}, {"\xCF\x88", "ps"}, {"\xCE\xA9", "O"}, {"\xCF\x89", "o"},
    {"\xCC\x81", ""}, {"\xCE\x84", ""}
};
int dict_size = sizeof(dict) / sizeof(dict[0]);

// Συναρτήσεις μετατροπής
void trim_string(char* str) { int len = strlen(str); while (len > 0 && (str[len-1] == ' ' || str[len-1] == '\n' || str[len-1] == '\r' || str[len-1] == '\t')) { str[len-1] = '\0'; len--; } }
void convert_to_greeklish(const char* input, char* output) { int i = 0, out_idx = 0, j; int in_len = strlen(input); while (i < in_len) { int matched = 0; for (j = 0; j < dict_size; j++) { int r_len = strlen(dict[j].grk); if (strncmp(&input[i], dict[j].grk, r_len) == 0) { strcpy(&output[out_idx], dict[j].lat); out_idx += strlen(dict[j].lat); i += r_len; matched = 1; break; } } if (!matched) { output[out_idx++] = input[i++]; } } output[out_idx] = '\0'; }

// Βοηθητική συνάρτηση για Unicode Ελληνικά
void SetTextGR(HWND hwnd, const char* text) { wchar_t wText[1024]; MultiByteToWideChar(1253, 0, text, -1, wText, 1024); SetWindowTextW(hwnd, wText); }

// WndProc
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CREATE: {
            // 1. Δημιουργία σκούρου πινέλου (RGB: 26, 26, 26 - Σκούρο Γκρι/Ανθρακί)
            hBackBrush = CreateSolidBrush(RGB(26, 26, 26));
            // 2. Δημιουργία BOLD γραμματοσειρών (Segoe UI)
            // Font για τον τίτλο (μικρότερο)
            hFontTitle = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");
            // Font για το τραγούδι (μεγαλύτερο, έντονο Neon effect)
            hFontSong = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");
            // 3. Δημιουργία των δύο Labels (Static controls)
            // Label 1: Ο Τίτλος "ΤΩΡΑ ΠΑΙΖΕΙ:"
            hLabelTitle = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX, 30, 20, 600, 30, /* Θέση και Μέγεθος (X, Y, Πλάτος, Ύψος) */hwnd, (HMENU)ID_LABEL_TITLE, NULL, NULL);
            SendMessage(hLabelTitle, WM_SETFONT, (WPARAM)hFontTitle, TRUE);
            SetTextGR(hLabelTitle, "ΤΩΡΑ ΠΑΙΖΕΙ:");
            // Label 2: Όνομα τραγουδιού
            hLabelSong = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT, 30, 60, 600, 150, /* Ύψος 150 για να χωράει 3-4 γραμμές */hwnd, (HMENU)ID_LABEL_SONG, NULL, NULL);
            SendMessage(hLabelSong, WM_SETFONT, (WPARAM)hFontSong, TRUE);
            SetTextGR(hLabelSong, "Αναμονή για μουσική...");
            // 4. Έναρξη χρονομέτρου
            SetTimer(hwnd, ID_TIMER, 2000, NULL);
            break;
        }
        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            HWND hwndControl = (HWND)lParam;
            // Φόντο *πίσω* από το κείμενο να είναι το ίδιο σκούρο
            SetBkColor(hdcStatic, RGB(26, 26, 26));
            if (hwndControl == hLabelTitle) {
                // Χρώμα για τον τίτλο: Λευκό BOLD
                SetTextColor(hdcStatic, RGB(245, 245, 245));
                return (LRESULT)hBackBrush; // Επιστροφή του σκούρου πινέλου για το φόντο
            } else if (hwndControl == hLabelSong) {
                // Χρώμα για το τραγούδι: ΕΝΤΟΝΟ NEON BLUE BOLD
                SetTextColor(hdcStatic, RGB(0, 180, 255));
                return (LRESULT)hBackBrush;
            }
            break;
        }
        case WM_TIMER: {
            // Εκτελείται κάθε 2 δευτερόλεπτα
            FILE *in = fopen(INPUT_FILE, "rb"); 
            if (in) {
                char current_content[2048] = {0};
                int bytes = fread(current_content, 1, sizeof(current_content) - 1, in);
                current_content[bytes] = '\0';
                fclose(in);
                int start = 0;
                if (bytes >= 3 && (unsigned char)current_content[0] == 0xEF && (unsigned char)current_content[1] == 0xBB && (unsigned char)current_content[2] == 0xBF) {
                    start = 3;
                }
                trim_string(&current_content[start]);
                if (strlen(&current_content[start]) > 2) { // Έλεγχος αν υπάρχει όνομα
                    char greeklish_content[4096] = {0};
                    convert_to_greeklish(&current_content[start], greeklish_content);
                    if (strcmp(greeklish_content, last_written_content) != 0) {
                        FILE *out = fopen(OUTPUT_FILE, "wb"); 
                        if (out) {
                            fwrite(greeklish_content, 1, strlen(greeklish_content), out);
                            fclose(out);
                            // Ανανέωση ΜΟΝΟ του Label με το όνομα του τραγουδιού
                            SetTextGR(hLabelSong, greeklish_content);
                            strcpy(last_written_content, greeklish_content);
                        }
                    }
                }
            }
            break;
        }
        case WM_DESTROY:
            // ΚΑΘΑΡΙΣΜΟΣ ΜΝΗΜΗΣ (GDI)
            DeleteObject(hFontTitle);
            DeleteObject(hFontSong);
            DeleteObject(hBackBrush);
            KillTimer(hwnd, ID_TIMER);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ΕΚΚΙΝΗΣΗ (WinMain)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    // Φόντο παραθύρου
    wc.hbrBackground = CreateSolidBrush(RGB(26, 26, 26));
    wc.lpszClassName = "RadioGreeklishApp";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    if (!RegisterClass(&wc)) return 0;
    HWND hwnd = CreateWindowEx(0, "RadioGreeklishApp", "", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 680, 280, NULL, NULL, hInstance, NULL);
    // Τίτλος παραθύρου
    SetTextGR(hwnd, "Radio - Greeklish Live Converter");
    ShowWindow(hwnd, nCmdShow);
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
// by Konstantinos2106 ( https://github.com/Konstantinos2106 )
// Version 1.0 - 21/5/2026
