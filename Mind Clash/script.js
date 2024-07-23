
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const port = new SerialPort('COM3', { baudRate: 9600 });

const parser = port.pipe(new Readline({ delimiter: '\n' }));

parser.on('data', data => {
    console.log('Recebido:', data);
});

port.on('open', () => {
    console.log('Conexão serial aberta com sucesso.');
});

parser.on('data', data => {
   
    const score = parseInt(data.trim(), 10); 

    
    updateScore(score);
});


function updateScore(score) {
    document.getElementById('first-score').textContent = score;

function updateScore(score) {
    document.getElementById('first-score').textContent = score;
    
}


port.on('open', () => {
    console.log('Conexão serial aberta com sucesso.');
});


port.on('error', (err) => {
    console.error('Erro na conexão serial:', err.message);
});
}
