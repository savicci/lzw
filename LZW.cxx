#include"LZW.hxx"

//dziala to tak ze 12 bitow jest podzielone miedzy pomiedzy 8 bitow(bajt) ktory jest zapisany i reszte
//ktora zmienia leftover na true. nastepnym razem zapisujac 12 bitow sprawdzamy leftover zapisujemy 4 bity
//w lewo od obecnego a potem pozostale 8 jako bajt

bool leftover = false;
int leftoverBits;

void writeBinary(FILE * output, int code) {
    if (leftover) {
        int previousCode = (leftoverBits << 4) + (code >> 8);
        
        fputc(previousCode, output);
        fputc(code, output);
        
        leftover = false; // no leftover now
    } else {
        leftoverBits = code & 0xF; // save leftover, the last 00001111
        leftover = true;
        
        fputc(code >> 4, output);
    }
}

int readBinary(FILE * input) {
    int code = fgetc(input);    
    if (code == EOF) return 0;

    if (leftover) {
        code = (leftoverBits << 8) + code;
        
        leftover = false;
    } else {
        int nextCode = fgetc(input);
        
        leftoverBits = nextCode & 0xF; // save leftover, the last 00001111
        leftover = true;
        
        code = (code << 4) + (nextCode >> 4);
    }
    return code;
}

//-------------------WERSJA 1------------------------
//-------------nie uzywa kodowania binarnego---------

void LZW::compress(){
//zmienne pomocnicze
    char s;
    char c;

    //nasz slownik
    std::map<std::string,CodeType> dictionary;        
        
    //wynik kompresji
    //std::vector<CodeType> result;

    //wypelnienie slownika
    int code;
    for(code=0; code<256; code++)
        dictionary[{(char)code}]=code;
        
    //na trzymanie stringu c
    std::string str;

    //wczytanie pierwszego znaku
    cin.get(c);

    //str od teraz pelni role c
    str.push_back(c);

    while(cin.get(s)){
        if(dictionary.count(str+s)!=0){
            str+=s;
        }
        else{
            cout.write((const char*)&dictionary.at(str),sizeof(CodeType));
            dictionary[str+s]=code;
            code++;
            str=s;
        }

    }

    //nalezy dodac to co zostalo po petli
    cout.write((const char*)&dictionary.at(str),sizeof(CodeType));

    return;
}


void LZW::decompress(){
    //slownik
    std::map<CodeType,std::string> dictionary;


    //wypelnienie slownika
    CodeType code;
    for(code=0;code<256;code++)
        dictionary[code]=(char)code;


    //pierwszy kod skompresowanych danych
    CodeType pk;
    cin.read((char*)&pk,sizeof(CodeType));
    cout<<dictionary.at(pk);
        
    //petla po wszystkich danych
    std::string pc;
    CodeType k;
    while(cin.read((char*)&k,sizeof(CodeType))){

        //ciag skojarzony z kodem
        pc=dictionary.at(pk);

        if(dictionary.count(k)!=0){
            dictionary[code]=pc+dictionary.at(k)[0];
            code++;

            cout<<dictionary.at(k);
        }   
        else{
            //przypadek specjalny- ciag postaci scscs
            dictionary[code]=pc+pc[0];
            code++;

            cout<<pc+pc[0];
        }
        pk=k;
    }

    return;
}


// void LZW::compress(){
//     //zmienne pomocnicze
//     char s;
//     char c;

//     //nasz slownik
//     std::map<std::string,CodeType> dictionary;        

//     //wypelnienie slownika
//     int code;
//     for(code=0; code<256; code++)
//         dictionary[{(char)code}]=code;
        
//     //na trzymanie stringu c
//     std::string str;

//     //wczytanie pierwszego znaku
//     c=fgetc(stdin);

//     //str od teraz pelni role c
//     str.push_back(c);

//     while((s=fgetc(stdin))!=EOF){
//         if(dictionary.count(str+s)!=0){
//             str+=s;
//         }
//         else{
//             writeBinary(stdout,dictionary.at(str));
//             dictionary[str+s]=code;
//             code++;
//             str=s;
//         }

//     }

//     //nalezy dodac to co zostalo po petli
//     writeBinary(stdout,dictionary.at(str));


//     return;
// }


// void LZW::decompress(){
//     //slownik
//     std::map<CodeType,std::string> dictionary;

//     //wypelnienie slownika
//     CodeType code;
//     for(code=0;code<256;code++)
//         dictionary[code]=(char)code;

//     //pierwszy kod skompresowanych danych
//     CodeType pk;

//     //wczytaj pierwszy znak i zapisz go na wyjscie
//     pk=readBinary(stdin);
//     //fprintf(stdout,dictionary.at(pk).c_str());
//     cout<<dictionary.at(pk);
        
//     //petla po wszystkich danych
//     std::string pc;
//     CodeType k;
//     while(k=readBinary(stdin)){
//         //ciag skojarzony z kodem
//         pc=dictionary.at(pk);

//         if(dictionary.count(k)!=0){
//             dictionary[code]=pc+dictionary.at(k)[0];
//             code++;
//             //fprintf(stdout,dictionary.at(k).c_str());
//             cout<<dictionary.at(k);
//         }   
//         else{
//             //przypadek specjalny- ciag postaci scscs- na przyklad booop
//             dictionary[code]=pc+pc[0];
//             code++;
//             //fprintf(stdout,pc.c_str());
//             //fputc(pc[0],stdout);
//             cout<<pc+pc[0];
//         }
//         pk=k;
//     }

//     return;
// }