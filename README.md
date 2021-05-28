# EstufaInteligente
Projeto de Objetos Inteligentes Conectados

Nosso projeto consistem em um ambiente controlado para que você possa dar uma melhor estimativa de vida para sua planta.
Assim monitoramos algumas variavveis como temperatura e umidade do vaso para manter sua planta sempre nas melhores condições.

Primeiramente, como ponto central do projeto temos 
    . Uma placa arduino uno

    . uma placa de prototipação com alguns jumpers

    . Um modulo relé de dois canais

Ligados ao arduino temos dois sensores:

    . Sensor de umidade 

    . Sensor de temperatura lm35

Os dois são responsaveis por fornecer as informaçoes que o arduino precisa para controlar seus atuadores.


Dessa forma podes interferir no comportamento dos seguintes atuadores:

    . Lampada led

    . Bomba de aquario

    . Cooler 12V

A lampada e o cooler servem para controlarmos a temperatura, dessa forma mantendo na temperatura ideal para a planta que você possuir.
A lampada também tem a funcao de oferecer a quantidade de luz correta para o bom desenvolviemnto de sua planta.

Enquanto isso a bomba de aquario joga a agua de um reservatório para o vaso de sua plantinha.

Para acionarmos a lampada e a bomba d'agua, utilizamos de um modulo relé para interromper a conexão de ambos com a tomada. dessa forma tudo o que precisamos são duas tomadas ou uma regua de tomada para podermos liguar o projeto.

O projeto consiste no monitoramento dos dois pinos dos sensores.
Com essas informaçoes coletadas e mapeadas das entradas analogicas, realizamos algumas comparacoes com os valores escolhidos para sua planta e assim o arduino decide se ira ligar algum atuador correspondete ou desliga-lo.


Como protocolo MQTT nosso projeto joga na rede wifi os dados que está lendo dos sensores para que um segundo código à escolha do usuario capture essas informações e exiba em seu computador e/ou celular