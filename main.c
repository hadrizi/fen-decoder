#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Terminal escape sequences
#define WHITE_BG 107
#define BLACK_BG 40

#define WHITE_FG 37
#define BLACK_FG 30

#define RESET "\033[0m"

// Chess symbols Unicode codes
#define PAWN_WHITE      0x2659
#define KING_WHITE      0x2654
#define QUEEN_WHITE     0x2655
#define ROOK_WHITE      0x2656
#define BISHOP_WHITE    0x2657
#define KNIGHT_WHITE    0x2658
#define PAWN_BLACK      0x265F
#define KING_BLACK      0x265A
#define QUEEN_BLACK     0x265B
#define ROOK_BLACK      0x265C
#define BISHOP_BLACK    0x265D
#define KNIGHT_BLACK    0x265E

int char_to_piece(char piece) {
    switch (piece)
    {
    case 'P':
        return PAWN_WHITE;
    case 'N':
        return KNIGHT_WHITE;
    case 'B':
        return BISHOP_WHITE;
    case 'R':
        return ROOK_WHITE;
    case 'Q':
        return QUEEN_WHITE;
    case 'K':
        return KING_WHITE;
    case 'p':
        return PAWN_BLACK;
    case 'n':
        return KNIGHT_BLACK;
    case 'b':
        return BISHOP_BLACK;
    case 'r':
        return ROOK_BLACK;
    case 'q':
        return QUEEN_BLACK;
    case 'k':
        return KING_BLACK;
    
    default:
        return 0x003F;
    }
}

int main(int argc, char const *argv[])
{
    setlocale(LC_CTYPE, "");
    bool symbol_mode = false;

    char pieces[64] = {0};

    const char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    if (argc >= 2) {
        fen = argv[1];
        
        if (strcmp(argv[2], "-s") == 0) symbol_mode = true;
    };

    size_t fen_i = 0, idx = 0;
    while (fen_i < strlen(fen)) {
        if (fen[fen_i] == '/') {
            fen_i++;
            continue;
        }

        if (!isdigit(fen[fen_i])) {
            pieces[idx] = fen[fen_i];
            idx++;
        }
        else idx += fen[fen_i] - '0';
        fen_i++;
    }
    

    int current_bg = WHITE_BG; 
    for (size_t i = 0; i < 64; i++) {
        printf("\033[30;%dm", current_bg);
        
        if (pieces[i] != 0) {
            if (!isupper(char_to_piece(pieces[i]))) printf("\033[37;%dm", current_bg);
            else printf("\033[30;%dm", current_bg);
            
            if (symbol_mode) printf("%c ", pieces[i]);
            else printf("%lc ", char_to_piece(pieces[i]));
        } else printf("  ");

        printf("\033[0m");
        if ((i + 1) % 8 == 0) printf("\n");
        else current_bg = current_bg == WHITE_BG ? BLACK_BG : WHITE_BG;
    }
    return 0;
}
