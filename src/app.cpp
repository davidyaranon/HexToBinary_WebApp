#include <server.h>
#include <BinaryHexDecimal.h>
#include <iostream>

using namespace crowJSON;

int main(int argc, char** argv)
{
  Server server(argc, argv);
  server.renderHTML("/", "index.html");

  server.route("/clickButton", [&](const request& req, response&res)
  {
    if((req.url_params.hasKey("hexValue")) 
    && (req.url_params.hasKey("littleEndian")))
    {
      std::string hex = req.url_params.get("hexValue");
      std::string little = req.url_params.get("littleEndian");

      json binary = hexToBinary(hex);
      json littleEndianBinary = hexToBinary(little);

      std::string leb = littleEndianBinary["binary"];
      long led = littleEndianBinary["decimal"];
      binary["littleEndian"] = leb;
      binary["decimalLittleEndian"] = led;

      res.sendJSON(binary);
    }
    else
    {
      res.sendError400();
    }

  });

  server.run();
}
