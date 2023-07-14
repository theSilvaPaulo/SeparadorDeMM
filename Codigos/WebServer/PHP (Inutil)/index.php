<!DOCTYPE html>
<html>
	<head>
		<title>M&M Sorting Machine</title>
		
		<script>
			var numTotal = 10;
			var numVermelho = 1;
			var numAmarelo = 3;
			var numAzul = 4;
			var numMarrom = 0;
			var numVerde = 2;
			var numLaranja = 8;

			function recarregar(){
				alert('Voce clicou em recarregar!');
				document.getElementById('totalSeparado').innerHTML = numTotal;
				document.getElementById('totalVermelho').innerHTML = numVermelho;
				document.getElementById('totalAmarelo').innerHTML = numAmarelo;
				document.getElementById('totalVerde').innerHTML = numVerde;
				document.getElementById('totalMarrom').innerHTML = numMarrom;
				document.getElementById('totalAzul').innerHTML = numAzul;
				document.getElementById('totalAzul').innerHTML = numLaranja;
			}
		</script>
		
		<style>
			p{
				display:inline-block;
			}
		</style>
	</head>

	<body>
		<div>
			<p>Numero de M&Ms separados!: </p>
			<?php
				echo "Dor e sofrimento";
				$total = $_POST["numeroTotal"];
				$myfile = fopen("arquivo.txt", "w") or die("Unable to open file!");
				fwrite($myfile, $total);
				fclose($myfile);
				echo $total;
			?>
			<br><!--
			<p>Numero de M&Ms vermelhos: </p><?php //echo $vermelho; ?>
			<br>
			<p>Numero de M&Ms amarelos: </p><?php //echo $amarelo; ?>
			<br>
			<p>Numero de M&Ms verdes: </p><?php //echo $azul; ?>
			<br>
			<p>Numero de M&Ms marrons: </p><?php //echo $verde; ?>
			<br>
			<p>Numero de M&Ms azuis: </p><?php //echo $marrom; ?>
			<br>
			<p>Numero de M&Ms laranjas: </p><?php //echo $laranja; ?>
			<br>
			<button type = 'button' onclick='recarregar()'>Recarregar</button>
			<img src="https://s10.postimg.org/ylfw5u7u1/backgroung_MM_Texted_min.png">-->
		</div>
	</body>
</html>