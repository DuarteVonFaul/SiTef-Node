#include "sitef.hpp"   
#include <string>
#include "./promises/imports.hpp"


#ifdef _WIN32
    HMODULE handler;
#endif

Value pathDLL(const CallbackInfo &info){
    Env env = info.Env();

    if (handler)
        return Boolean::New(env, true);

    if (info.Length() < 1)
        napi_throw_error(env, "0", "Informe o caminho da DLL.");
    else if (!info[0].IsString())
        napi_throw_type_error(env, "1", "O caminho informado não é uma string válida.");
    else
    {
        std::string sw = info[0].ToString().Utf8Value();
        std::wstring path = std::wstring(sw.begin(), sw.end());
        #ifdef _WIN32
            handler = LoadLibraryW(path.c_str());
        #endif

    if (!handler)
        napi_throw_type_error(env, "2", "Não foi possível carregar a DLL.");
    else
        return Boolean::New(env, true);
    }

    return env.Null();
}

int configSiTef(const char *ip, const char *terminal, const char *loja, const char *reservado, const char *parametrosAdicionais){
    if (!handler)
        throw("Carregue a DLL do SiTef!");

    #ifdef _WIN32
        ConfiguraIntSiTefInterativoEx configuraSitef = (ConfiguraIntSiTefInterativoEx)GetProcAddress(handler, "ConfiguraIntSiTefInterativoEx");
    #endif

    return configuraSitef(ip,
                          terminal,
                          loja,
                          reservado,
                          parametrosAdicionais);
}

int checkPinPad(){
    if (!handler)
        throw("Carregue a DLL do SiTef!");

    #ifdef _WIN32
        VerificaPresencaPinPad verificaPresenca = (VerificaPresencaPinPad)GetProcAddress(handler, "VerificaPresencaPinPad");
    #endif

    return verificaPresenca();
}

int woutPermanentPinPad(const char *mensagem){
    if (!handler)
        throw("Carregue a DLL do SiTef!");

    #ifdef _WIN32
        EscreveMensagemPermanentePinPad escreveMensagem = (EscreveMensagemPermanentePinPad)GetProcAddress(handler, "EscreveMensagemPermanentePinPad");
    #endif

    return escreveMensagem(mensagem);
}

int binaryPinPad(const char *mensagem){
    if (!handler)
        throw("Carregue a DLL do SiTef!");

    #ifdef _WIN32
        LeSimNaoPinPad escreveMensagem = (LeSimNaoPinPad)GetProcAddress(handler, "LeSimNaoPinPad");
    #endif

    return escreveMensagem(mensagem);
}

int initSiTef(int funcao, const char *valor, const char *cupomFiscal, const char *dataFiscal, const char *horaFiscal, const char *operador, const char *paramAdicionais){
    if (!handler)
        throw("Carregue a DLL do SiTef!");

    #ifdef _WIN32
        IniciaFuncaoSiTefInterativo iniciaFuncao = (IniciaFuncaoSiTefInterativo)GetProcAddress(handler, "IniciaFuncaoSiTefInterativo");
    #endif

    return iniciaFuncao(funcao,
                        valor,
                        cupomFiscal,
                        dataFiscal,
                        horaFiscal,
                        operador,
                        paramAdicionais);
}

int contSitef(int *comando, long *tipoCampo, int *tamMinimo, int *tamMaximo, char *buffer, int tamBuffer, int continua){
    if (!handler)
        throw("Carregue a DLL do SiTef!");

    #ifdef _WIN32
        ContinuaFuncaoSiTefInterativo continuaFuncao = (ContinuaFuncaoSiTefInterativo)GetProcAddress(handler, "ContinuaFuncaoSiTefInterativo");
    #endif

    return continuaFuncao(comando,
                          tipoCampo,
                          tamMinimo,
                          tamMaximo,
                          buffer,
                          tamBuffer,
                          continua);
}

void finallySiTef(int confirma, const char *cupomFiscal, const char *dataFiscal, const char *horaFiscal, const char *paramAdicionais){
    if (!handler)
        throw("Carregue a DLL do SiTef!");

    #ifdef _WIN32
        FinalizaFuncaoSiTefInterativo finalizaFuncao = (FinalizaFuncaoSiTefInterativo)GetProcAddress(handler, "FinalizaFuncaoSiTefInterativo");
    #endif

    finalizaFuncao(confirma, 
                   cupomFiscal, 
                   dataFiscal, 
                   horaFiscal, 
                   paramAdicionais);
}

Napi::Object Init(Napi::Env env, Napi::Object exports){
              
  exports.Set(Napi::String::New(env, "pathDLL"), 
              Napi::Function::New(env, pathDLL));

  exports.Set(Napi::String::New(env, "configSiTef"),
             Napi::Function::New(env, ConfigPromise::Create));

  exports.Set(Napi::String::New(env, "initSiTef"),
             Napi::Function::New(env, InitPromise::Create));
  exports.Set(Napi::String::New(env, "woutPermanentPinPad"),
             Napi::Function::New(env, WoutPinPadPromise::Create));

  
  return exports;
}

NODE_API_MODULE(addon, Init)