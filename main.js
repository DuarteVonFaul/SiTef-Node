const Sitef = require('./build/Release/node-sitef.node');




async function Promises() {
  try {
    const result = await Sitef.pathDLL("to\\path\\CliSiTef64I.dll");
    console.log(result);

    const result2 = await Sitef.configSiTef("127.0.0.1:4096",
                                            "00000000",
                                            "HH000001",
                                            "0",
                                            "");
    console.log(result2);

    const result3 = await Sitef.initSiTef(2,
                                          "0.50",
                                          "123456",
                                          "20230223",
                                          "092020",
                                          "003",
                                          "");
    console.log(result3);

    let result4
    do{

      if(result4){
        if(result4.comando == 21){
          const result = await Sitef.contSitef(0,
                                              0,
                                              0,
                                              0,
                                              "1",
                                              20000,
                                              0);

          console.log(result);
          result4 = result;
        }else{
          const result = await Sitef.contSitef( 0,
                                                0,
                                                0,
                                                0,
                                                "",
                                                20000,
                                                0);

          console.log(result);
          result4 = result;
        }
      
        
      }else{

        const result = await Sitef.contSitef(0,
                                            0,
                                            0,
                                            0,
                                            "",
                                            20000,
                                            0);

        console.log(result);
        result4 = result;
        
      }

      
      
    }while(result4.retorno == 10000)
    
    const result5 = await Sitef.finallySiTef( 0,
                                              "123456",
                                              "20230223",
                                              "092020",
                                              "")
    

  } catch (error) {
    console.error(error);
  }
}

Promises();
