$(document).ready(function(){});

function getInput()
{
  let hexValue = document.getElementById("hex").value.toUpperCase();

  if(hexValue[0] == '0' && hexValue[1] == 'X')
  {
    hexValue = hexValue.substring(2);
  }
  if(hexValue.length > 16)
  {
    alert("16 bit limit, sorry :(");
  }
  else 
  {
    if(hexValue.length % 2 != 0)
    {
      hexValue = '0' + hexValue;
    }
    let littleEndian = "";
    for(let i = hexValue.length - 1; i >= 0; i -= 2)
    {
      littleEndian += hexValue.substring(i - 1, (i + 1));
    }
    hexToBinary(hexValue, littleEndian);
  } 
}

function hexToBinary(hexValue, littleEndian)
{
  $.get("/clickButton", {"hexValue" : hexValue, "littleEndian" : littleEndian}, function(response)
  {
    let data = JSON.parse(response);

    $("#displayArea").html("Hex is: " + data["hex"] + " (" + hexValue.length / 2 + " bytes)<br>\r\n Binary is: " + data["binary"] + "<br>\r\n Decimal is: " + data["decimal"] + "<br>\r\n Binary (little-endian) is: " + data["littleEndian"] + "<br>\r\n Decimal (little-endian) is: " + data["decimalLittleEndian"]);

  });
}

