#include"LZW.hxx"

int main(int argc, char const *argv[])
{
    if(argc!=2 ){
        cout<<"Prawidlowe opcje wywolania programu"<<endl;
        cout<<"-c - opcja kompresji. Przyjmuje plik z wejscia i zwraca na wyjscie."<<endl;
        cout<<"-d - opcja dekompresji. Przyjmuje skompresowany plik z wejscia i zwraca na wyjscie"<<endl;
        cout<<"Aby przekierowac z/do plikow uzyj < / >"<<endl;
        exit(-1);
    }

    LZW lzw;

    try{
        std::string option(argv[1]);
        
        if(option=="-c"){
            lzw.compress();
        }
        else if(option=="-d"){
            lzw.decompress();
        }
        else{
            std::cerr<<"Nieznane polecenie"<<endl;
            exit(-1);
        }

    }catch(std::exception& e){
        std::cerr<<e.what()<<endl;
    }


    return 0;
}
