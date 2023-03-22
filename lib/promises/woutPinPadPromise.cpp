#ifndef WOUTPINPAD_H
#define WOUTPINPAD_H

  #include "promise.cpp"
  #include "../sitef.hpp"

  using std::string;

  class WoutPinPadPromise : public Promise<int>
  {
  public:
    static Value Create(const CallbackInfo &info){
      if (info.Length() < 1)
        return Reject(info.Env(), "MissingArgument");
      else if (!info[0].IsString())
        return Reject(info.Env(), "InvalidArgument");

      string mensagem = info[0].As<Napi::String>().Utf8Value();
      WoutPinPadPromise *worker = new WoutPinPadPromise(info.Env(), mensagem);
      worker->Queue();
      return worker->deferred.Promise();
    }

  protected:
    void Execute() override  {
      result = woutPermanentPinPad(mensagem.c_str());
    }

    virtual void OnOK() override
    {
      deferred.Resolve(Number::New(Env(), result));
    }

  private:
    WoutPinPadPromise(napi_env env, 
                      string &p_mensagem) : Promise(env), 
                                            mensagem(p_mensagem) {}

    string mensagem;
  };

#endif