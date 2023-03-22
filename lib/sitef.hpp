#include <napi.h>
#include <string.h>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#endif

using Napi::Boolean;
using Napi::CallbackInfo;
using Napi::Env;
using Napi::Error;
using Napi::Function;
using Napi::Number;
using Napi::Object;
using Napi::String;
using Napi::TypeError;
using Napi::Value;

using std::string;

#ifndef SITEF_H // include guard
#define SITEF_H 1


// Tipos dos métodos do SiTef
typedef int (*VerificaPresencaPinPad)();
typedef int (*ConfiguraIntSiTefInterativoEx)(const char *, const char *, const char *, const char *, const char *);
typedef int (*IniciaFuncaoSiTefInterativo)(int, const char *, const char *, const char *, const char *, const char *, const char *);
typedef int (*ContinuaFuncaoSiTefInterativo)(int *, long *, int *, int *, const char *, int, int);
typedef void (*FinalizaFuncaoSiTefInterativo)(short, const char *, const char *, const char *, const char *);
typedef int (*EscreveMensagemPermanentePinPad)(const char *);
typedef int (*LeSimNaoPinPad)(const char *);

Value pathDLL(const CallbackInfo &info);

int checkPinPad();
int configSiTef(const char *, const char *, const char *, const char *, const char *);
int woutPermanentPinPad(const char *);
int binaryPinPad(const char *);
int initSiTef(int, const char *, const char *, const char *, const char *, const char *, const char *);
int contSitef(int *comando, long *tipoCampo, int *tamMinimo, int *tamMaximo, char *buffer, int tamBuffer, int continua);
void finallySiTef(int confirma, const char *cupomFiscal, const char *dataFiscal, const char *horaFiscal, const char *paramAdicionais);

#endif /* SITEF_H */