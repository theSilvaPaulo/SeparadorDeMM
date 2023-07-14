/*********VARIAVEIS**********/
var intervalo;
var intervaloAoVivo;

var total = 0;
var vermelho = 0;
var amarelo = 0;
var azul = 0;
var verde = 0;
var laranja = 0;
var marrom = 0;

var lastVermelho = 0;
var lastAmarelo = 0;
var lastAzul = 0;
var lastVerde = 0;
var lastLaranja = 0;
var lastMarrom = 0;

//Pra funcao de rodar
var delta = 10;
var intervaloRodaRoda;
var idCor = "none";

/******TRATA O OBJETO RECEM JS E PEGA OS DADOS INDIVIDUAIS*****/
function trataDados(dadosMM){
	//Altera os lastCor
	lastVermelho = vermelho;
	lastAmarelo = amarelo;
	lastAzul = azul;
	lastVerde = verde;
	lastLaranja = laranja;
	lastMarrom = marrom;

	//Seta os dados recebidos nas variaveis
	total = dadosMM.variables.total;
	vermelho = dadosMM.variables.vermelho;
	amarelo = dadosMM.variables.amarelo;
	azul = dadosMM.variables.azul;
	verde = dadosMM.variables.verde;
	laranja = dadosMM.variables.laranja;
	marrom = dadosMM.variables.marrom;

	//Da console.log nos dados recebidos
	console.log(dadosMM);
	console.log("TOTAL: " + total);
	console.log("VERMELHO: " + vermelho);
	console.log("AMARELO: " + amarelo);
	console.log("AZUL: " + azul);
	console.log("VERDE: " + verde);
	console.log("LARANJA: " + laranja);
	console.log("MARROM: " + marrom);

	//Altera os <p> para os dados recebidos
	document.getElementById("quantidadeVermelho").innerHTML = vermelho;
	document.getElementById("quantidadeAmarelo").innerHTML = amarelo;
	document.getElementById("quantidadeAzul").innerHTML = azul;
	document.getElementById("quantidadeVerde").innerHTML = verde;
	document.getElementById("quantidadeLaranja").innerHTML = laranja;
	document.getElementById("quantidadeMarrom").innerHTML = marrom;

	//Replota o grafico com os novos dados
	plotarGrafico();
}

/************PEGA O JSON ENVIADO PELO ARDUINO************/
function pegaJson(){
	var url = "http://192.168.0.16"; //Aqui vem o IP do arduino
	var xmlhttp = new XMLHttpRequest();
	var dadosMM; //Objeto que contem todos os dados do JSON

	//Pega o JSON enviado pelo Arduino e o transforma em objeto JS
	xmlhttp.onreadystatechange = function(){
		if(xmlhttp.readyState == 4 && xmlhttp.status == 200){
			dadosMM = JSON.parse(xmlhttp.responseText);
			console.log("LI JSON");
			trataDados(dadosMM);
			rodaRoda(); //Roda o m&m a ser rodado
		}
	};
	xmlhttp.open("GET", url, true);
	xmlhttp.send();
}

/**************PEGA O JSON A CADA 5 SEGUNDOS************/
function comecaComunicacao(){
	//Reseta os valores dos M&M's
	total = 0;
	vermelho = 0;
	amarelo = 0;
	azul = 0;
	verde = 0;
	laranja = 0;
	marrom = 0;
	document.getElementById("quantidadeVermelho").innerHTML = vermelho;
	document.getElementById("quantidadeAmarelo").innerHTML = amarelo;
	document.getElementById("quantidadeAzul").innerHTML = azul;
	document.getElementById("quantidadeVerde").innerHTML = verde;
	document.getElementById("quantidadeLaranja").innerHTML = laranja;
	document.getElementById("quantidadeMarrom").innerHTML = marrom;

	//Replota o grafico com os valores zerados
	plotarGrafico();

	//Desativa botao de comecar a separar e ativa o de parar
	document.getElementById("btnComecar").disabled = true; //Desativa comecar
	document.getElementById("btnParar").disabled = false; //Ativa parar
	
	pegaJson();
	intervalo = setInterval(pegaJson, 5000); //Intervalo pra pegar info

	document.getElementById("aoVivo").style.visibility = "visible"; //Deixa a bolinha visivel
	intervaloAoVivo = setInterval(piscaPisca, 1000); //Intervalo pra piscar bolinha
}

/**********PARA DE PEGAR O JSON A CADA 5 SEGUNDOS********/
function terminaComunicacao(){
	//Ativa botao de comecar e desativa botao de parar
	document.getElementById("btnComecar").disabled = false; //Ativa comecar
	document.getElementById("btnParar").disabled = true; //Desativa parar

	clearInterval(intervalo);

	document.getElementById("aoVivo").style.visibility = "hidden"; //Apaga a bolinha
	clearInterval(intervaloAoVivo);
}

/******************RODA RODA DOS M&M's****************/
function rodaRoda(){
	lastVermelho = 100;

	//Verifica qual m&m foi separado
	if(lastVermelho != vermelho) idCor = "imgVermelho";
	else if(lastAmarelo != amarelo) idCor = "imgAmarelo";
	else if(lastAzul != azul) idCor = "imgAzul";
	else if(lastVerde != verde) idCor = "imgVerde";
	else if(lastLaranja != laranja) idCor = "imgLaranja";
	else if(lastMarrom != marrom) idCor = "imgMarrom";
	else idCor = "none";

	intervaloRodaRoda = setInterval(rotateBy10Deg, 25);
}

function rotateBy10Deg(){
	document.getElementById(idCor).style.webkitTransform = "rotate("+delta+"deg)";
	if((delta % 360) == 0) clearInterval(intervaloRodaRoda);
	delta+=10;
}

/******************PISCA PISCA AO VIVO***************/
function piscaPisca(){
	var estado;

	//Pega o estado da bolinha
	estado = document.getElementById("aoVivo").style.visibility;

	//Verifica o estado e o altera em funcao do atual
	if(estado === "visible"){
		document.getElementById("aoVivo").style.visibility = "hidden"; //Apaga a bolinha
	}
	else{
		document.getElementById("aoVivo").style.visibility = "visible"; //Acende a bolinha
	}
}

/********************PLOTA GRAFICO*******************/
function plotarGrafico(){
	//Dados quantitativos do grafico de barras
	var trace1 = {
	  x: ['Vermelhos', 'Amarelo', 'Azul', 'Verde', 'Laranja', 'Marrom'],
	  y: [vermelho, amarelo, azul, verde, laranja ,marrom],
	  type: 'bar',
	  name: "M&M's Separados",
	  marker: {
	    color: ['rgb(238, 57, 50)', 'rgb(252, 187, 71)', 'rgb(1, 104, 163)', 'rgb(87, 205, 127)', 'rgb(255, 117, 9)', 'rgb(119, 79, 56)']
	  }
	};

	//Dados de layout do grafico de barras
	var layoutBarras = {
	  title: "M&M's Separados em Barras",

	  font: {
	    family: 'FonteMM, monospace',
	    size: 18,
	    color: '#7f7f7f'
	  },

	  xaxis: {
	    title: "Cor do M&M",
	    titlefont: {
	      family: 'Courier New, monospace',
	      size: 18,
	      color: '#7f7f7f'
	    }
	  },

	  yaxis: {
	    title: 'Número separado',
	    titlefont: {
	      family: 'Courier New, monospace',
	      size: 18,
	      color: '#7f7f7f'
	    }
	  }
	};

	//Definicao do data como apenas o grafico de barras
	var dataBarras = [trace1];


	//Dados quantitativos do grafico de pizza
	var trace2 = {
	  labels: ['Vermelhos', 'Amarelo', 'Azul', 'Verde', 'Laranja', 'Marrom'],
	  values: [vermelho, amarelo, azul, verde, laranja ,marrom],
	  type: 'pie',
	  name: "M&M's Separados",
	  marker: {
	    colors: ['rgb(238, 57, 50)', 'rgb(252, 187, 71)', 'rgb(1, 104, 163)', 'rgb(87, 205, 127)', 'rgb(255, 117, 9)', 'rgb(119, 79, 56)']
	  }
	};

	//Layout do grafico de pizza
	var layoutPizza = {
	  title: "M&M's Separados em Pizza",

	  font: {
	    family: 'FonteMM, monospace',
	    size: 18,
	    color: '#7f7f7f'
	  }
	};

	//Definicao do data como apenas o grafico de pizza
	var dataPizza = [trace2];


	Plotly.newPlot('graficoBarras', dataBarras, layoutBarras);
	Plotly.newPlot('graficoPizza', dataPizza, layoutPizza);
}