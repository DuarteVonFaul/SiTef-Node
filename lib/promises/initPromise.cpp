#ifndef INITSITEF_H
#define INITSITEF_H

    #include "promise.cpp"
    #include "../sitef.hpp"

    using std::string;

    class InitPromise : public Promise<int>
    {
        public:
            static Value Create(const CallbackInfo &info){
                if (info.Length() < 7)
                return Reject(info.Env(), "MissingArgument");
                else if (!info[0].IsNumber() || !info[1].IsString() || !info[2].IsString() || !info[3].IsString() ||
                        !info[4].IsString() || !info[5].IsString() || !info[6].IsString())
                return Reject(info.Env(), "InvalidArgument");

                int funcao = info[0].As<Napi::Number>().Int32Value();
                string valor = info[1].As<Napi::String>().Utf8Value();
                string cupomFiscal = info[2].As<Napi::String>().Utf8Value();
                string dataFiscal = info[3].As<Napi::String>().Utf8Value();
                string horaFiscal = info[4].As<Napi::String>().Utf8Value();
                string operador = info[5].As<Napi::String>().Utf8Value();
                string paramAdicionais = info[5].As<Napi::String>().Utf8Value();

                InitPromise *worker = new InitPromise(info.Env(), funcao, valor, cupomFiscal, dataFiscal, horaFiscal, operador, paramAdicionais);
                worker->Queue();
                return worker->deferred.Promise();
            }

        protected:
            void Execute() override     {
                result = initSiTef(funcao, valor.c_str(), cupomFiscal.c_str(), dataFiscal.c_str(), horaFiscal.c_str(), operador.c_str(), paramAdicionais.c_str());
            }

            virtual void OnOK() override     {
                deferred.Resolve(Number::New(Env(), result));
            }

        private:
            InitPromise(napi_env env,
                                int &p_funcao,
                                string &p_valor,
                                string &p_cupomFiscal,
                                string &p_dataFiscal,
                                string &p_horaFiscal,
                                string &p_operador,
                                string &p_paramAdicionais) : Promise(env),
                                                            funcao(p_funcao),
                                                            valor(p_valor),
                                                            cupomFiscal(p_cupomFiscal),
                                                            dataFiscal(p_dataFiscal),
                                                            horaFiscal(p_horaFiscal),
                                                            operador(p_operador),
                                                            paramAdicionais(p_paramAdicionais) {}

            int funcao;
            string valor;
            string cupomFiscal;
            string dataFiscal;
            string horaFiscal;
            string operador;
            string paramAdicionais;
    };

#endif