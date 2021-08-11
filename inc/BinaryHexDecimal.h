#include <server.h>
#include <time.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <random>
#include <iostream>
#include <vector>

static const unsigned long long hextable[] =
{ 
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1, 0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,14,15,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};


crowJSON::json hexToBinary(std::string hex)
{
  crowJSON::json j;
  j["hex"] = "0x" + hex;
  if (hex[std::strspn(hex.c_str(), "0123456789ABCDEF")] == 0)
  {
    std::string binary = "";
    for(auto& c : hex)
    {
      int letter = 0;
      std::string digit = "";
      if(std::isalpha(c))
      {
        letter = c - 55;
      }
      else 
      {
        letter = c - '0';
      }
      for(int i = 8; i > 0; i /= 2)
      {
        if(letter - i >= 0)
        {
          digit += '1';
          letter -= i;
        }
        else 
        {
          digit += '0';
        }
      }
      binary += digit;
    }

    unsigned long long decimal = 0;
    const char* h = hex.c_str();
    while(*h && decimal >= 0)
    {
      decimal = (decimal << 4) | hextable[*h++];
    }

    j["binary"] = binary;
    j["decimal"] = decimal;
  }
  else
  {
    j["binary"] = "INVALID ENTRY";
    j["decimal"] = "INVALID ENTRY";
  }
  return j;
}