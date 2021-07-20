
//configure message
message="Measurement of density correlations in pseudorapidity via charged particle multiplicity fluctuations in Au+Au collisions at sqrt(s_NN) = 200 GeV";
//animate text in NS6? (0 will turn it off)
ns6switch=1;

var ns6=document.getElementById&&!document.all;
mes=new Array();
mes[0]=-1;
mes[1]=-4;
mes[2]=-7;
mes[3]=-10;
mes[4]=-7;
mes[5]=-4;
mes[6]=-1;
num=0;
num2=0;
txt="";
function jump0(){
  if(ns6&&!ns6switch){
    jump.innerHTML=message;
    return;
  }
  if(message.length > 6){
    for(i=0; i != message.length;i++){
      txt=txt+"<span style='position:relative;' id='n"+i+"'>"+message.charAt(i)+"</span>"
    }
    jump.innerHTML=txt;
    txt="";
    jump1a();
  }
  else{
    alert("Your message is to short");
  }
}

function jump1a(){
  nfinal=(document.getElementById)? document.getElementById("n0") : document.all.n0;
  nfinal.style.left=-num2;
  if(num2 != 9){
    num2=num2+3;
    setTimeout("jump1a()",50);
  }
  else{
    jump1b();
  }
}

function jump1b(){
  nfinal.style.left=-num2;
  if(num2 != 0){
    num2=num2-3;
    setTimeout("jump1b()",50);
  }
  else{
    jump2();
  }
}

function jump2(){
  txt="";
  for(i=0;i != message.length;i++){
    if(i+num > -1 && i+num < 7){
      txt=txt+"<span style='position:relative;top:"+mes[i+num]+"'>"+message.charAt(i)+"</span>";
    }
    else{
      txt=txt+"<span>"+message.charAt(i)+"</span>";
    }
  }
  jump.innerHTML=txt;
  txt="";
  if(num != (-message.length)){
    num--;
    setTimeout("jump2()",50);
  }
  else{
    num=0;
    setTimeout("jump0()",50);
  }
}

