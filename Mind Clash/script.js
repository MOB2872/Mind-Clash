<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Mind Clash</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <div id="home">
            <h1>Mind Clash</h1>
            <a href="#instructions" class="button">Entrar</a>
            <a href="#game" class="button">Começar</a>
        </div>
        <div id="instructions" class="hidden">
            <h2>Como jogar Mind Clash</h2>
            <img src="image1.jpg" alt="Imagem 1">
            <img src="image2.jpg" alt="Imagem 2">
            <p>Aqui estão as instruções sobre como jogar Mind Clash...</p>
            <a href="#home" class="button">Voltar</a>
        </div>
        <div id="game" class="hidden">
            <h2>Score</h2>
            <div class="score-board">
                <div>1º: <span id="first-score">0</span></div>
                <div>2º: <span id="second-score">0</span></div>
                <div>3º: <span id="third-score">0</span></div>
            </div>
            <a href="#home" class="button">Voltar</a>
        </div>
    </div>
    <script src="script.js"></script>
</body>
</html>
