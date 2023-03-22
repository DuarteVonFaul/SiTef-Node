#ifndef PROMISE_H
#define PROMISE_H

  #include <napi.h>

  template <class T>

  class Promise : public Napi::AsyncWorker{

      protected:
        
        virtual void OnError(const Napi::Error &e) override {
          //Rejeita a Promessa com um Erro
          deferred.Reject(e.Value());
        };

        static Napi::Value Reject(Napi::Env env, const char *msg){
          //Aqui eu crio uma Espera de uma Pomessa inicializando como uma Nova promessa recebendo o ambiente Env
          Napi::Promise::Deferred failed = Napi::Promise::Deferred::New(env);
          //Pego a rejeição da promessa, e inicializo um erro recebendo o Ambiente Env e uma mensagem e retorno o valor do erro
          failed.Reject(Napi::Error::New(env, msg).Value());
          //Por fim retorno a promessa rejeitada
          return failed.Promise();
        }

        //Metodo Construtor Responsavel por inicializar o meu deferred com o Ambiente da Promessa e meu result
        Promise(napi_env env) : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), result() {};

        T result;
        Napi::Promise::Deferred deferred;


  };

#endif