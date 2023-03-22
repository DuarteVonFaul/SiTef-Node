const Sitef = require('./build/Release/node-sitef.node');




async function Promises() {
  try {
    const result = await Sitef.pathDLL("C:\\Users\\Estagiario-03\\Desktop\\GitHub\\others\\softExpress\\app\\dll\\CliSiTef64I.dll");
    console.log(result);
    const result2 = await Sitef.configSiTef("127.0.0.1:4096",
                                            "00000000",
                                            "HH000001",
                                            "0",
                                            "");
    console.log(result2);
    const result3 = await Sitef.woutPermanentPinPad("SGE AUtomacao");
    console.log(result3);
  } catch (error) {
    console.error(error);
  }
}

Promises();