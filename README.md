# README

## Título
Robô Seguidor de Linha - Competição CORA UFMG

## Descrição
Este projeto foi desenvolvido para a competição de robôs autônomos (CORA) da UFMG. O robô é um seguidor de linha que utiliza sensores para detectar e seguir uma linha no chão. O código controla os motores do robô para garantir que ele siga a linha corretamente, faça curvas e pare quando necessário. O robô também conta quadrados detectados ao longo do caminho e executa ações específicas com base na contagem.

## Estrutura do Projeto
O projeto consiste em um único arquivo de código fonte:

- [`ultimatowstop.ino`](ultimatowstop.ino): Contém todo o código necessário para o funcionamento do robô seguidor de linha.

## Uso
Para utilizar este código, siga os passos abaixo:

1. **Configuração do Hardware**:
   - Conecte os sensores de linha aos pinos A1, A2, A3, A4 e A5 do Arduino.
   - Conecte os motores aos pinos 5 e 6 do Arduino para controle PWM.
   - Conecte os pinos de controle do CI 74HC595 aos pinos 4, 12, 8 e 7 do Arduino.

2. **Upload do Código**:
   - Abra o arquivo [`ultimatowstop.ino`](ultimatowstop.ino) no Arduino IDE.
   - Conecte o Arduino ao computador e selecione a porta correta no Arduino IDE.
   - Faça o upload do código para o Arduino.

3. **Execução**:
   - Coloque o robô na pista de linha.
   - Ligue o robô e ele começará a seguir a linha automaticamente.

## Funções Principais
- `setup()`: Configura os pinos de entrada e saída e inicializa a comunicação serial.
- `loop()`: Função principal que é executada continuamente. Controla a leitura dos sensores, a contagem de quadrados e o movimento dos motores.
- `ci74HC595Write(byte pino, bool estado)`: Função para escrever no CI 74HC595.
- `perdeuLinha()`: Verifica se o robô perdeu a linha.
- `pararRobo()`: Para o movimento do robô.
- `verificarQuadrado()`: Verifica a contagem de quadrados e executa ações de curva.

## Contribuição
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests para melhorias no código.

## Licença
Este projeto está licenciado sob a MIT License.

---

Desenvolvido para a competição de robôs autônomos (CORA) da UFMG.