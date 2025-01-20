
Dependências
- Python 3.x
- Biblioteca PySerial (para comunicação serial)
- Biblioteca Servo (para controle de servos)

Instalação das dependências
```
bash
pip install pyserial
pip install servo
```

Código
```
import serial
import time
import servo

Configuração dos servos
SERVOS = 5
MIN_ANGULO = 0
MAX_ANGULO = 360

Configuração da comunicação serial
PORTA_SERIAL = 'COM3'  # Altere para a porta serial correta
VEL SERIAL = 9600

Inicialização dos servos
servos = [servo.Servo(i) for i in range(SERVOS)]

Função para gravar movimentos
def gravar_movimento():
 nomemovimento = input("Nome do movimento: ")
  movimentos = []
   for i in range(3):  # 3 programações de movimentos
    print(f"Movimento {i+1}:")
     angulos = []
      for j in range(SERVOS):
       angulo = int(input(f"Ângulo servo {j+1}: "))
        angulos.append(angulo)
         movimentos.append(angulos)
          
           # Gravar movimentos em arquivo
            with open(f"{nomemovimento}.txt", "w") as arquivo:
             for movimento in movimentos:
              arquivo.write(" ".join(map(str, movimento)) + "\n")

              Função para reproduzir movimentos
              def reproduzir_movimento(nome_arquivo):
               try:
                with open(nome_arquivo, "r") as arquivo:
                 movimentos = [list(map(int, linha.split())) for linha in arquivo.readlines()]
                  for movimento in movimentos:
                   for i, angulo in enumerate(movimento):
                    servos[i].set_angle(angulo)
                     time.sleep(1)  # Intervalo entre movimentos
                      except FileNotFoundError:
                       print("Arquivo não encontrado.")

                       Função principal
                       def main():
                        serial.Serial(PORTA_SERIAL, VEL_SERIAL).close()  # Fechar porta serial
                         while True:
                          print("1. Gravar movimento")
                           print("2. Reproduzir movimento")
                            escolha = input("Escolha: ")
                             if escolha == "1":
                              gravar_movimento()
                               elif escolha == "2":
                                nome_arquivo = input("Nome do arquivo: ")
                                 reproduzir_movimento(nome_arquivo)
                                  else:
                                   print("Opção inválida.")

                                   if __name__ == "__main__":
                                    main()
                                    ```

                                    Uso
                                    1. Conecte os servos à placa de controle.
                                    2. Abra o terminal e execute o script.
                                    3. Escolha opção 1 para gravar movimentos.
                                    4. Insira os ângulos para cada servo.
                                    5. Escolha opção 2 para reproduzir movimentos.
                                    6. Insira o nome do arquivo com os movimentos gravados.

                                    Observações
                                    - Ajuste a porta serial e velocidade conforme necessário.
                                    - Certifique-se de que os servos estejam conectados corretamente.
                                    - O código assume que os servos sejam do tipo "servo contínuo" sem limites de rotação.
                                    [19/01, 22:52] Meta AI: Segue um exemplo de código em Python para controle de 5 servos, com gravação e reprodução de movimentos:

                                    Dependências
                                    - Python 3.x
                                    - Biblioteca PySerial (para comunicação serial)
                                    - Biblioteca Servo (para controle de servos)

                                    Instalação das dependências
                                    ```
                                    bash
                                    pip install pyserial
                                    pip install servo
                                    ```

                                    Código
                                    ```
                                    import serial
                                    import time
                                    import servo

                                    Configuração dos servos
                                    SERVOS = 5
                                    MIN_ANGULO = 0
                                    MAX_ANGULO = 360

                                    Configuração da comunicação serial
                                    PORTA_SERIAL = 'COM3'  # Altere para a porta serial correta
                                    VEL SERIAL = 9600

                                    Inicialização dos servos
                                    servos = [servo.Servo(i) for i in range(SERVOS)]

                                    Função para gravar movimentos
                                    def gravar_movimento():
                                     nomemovimento = input("Nome do movimento: ")
                                      movimentos = []
                                       for i in range(3):  # 3 programações de movimentos
                                        print(f"Movimento {i+1}:")
                                         angulos = []
                                          for j in range(SERVOS):
                                           angulo = int(input(f"Ângulo servo {j+1}: "))
                                            angulos.append(angulo)
                                             movimentos.append(angulos)
                                              
                                               # Gravar movimentos em arquivo
                                                with open(f"{nomemovimento}.txt", "w") as arquivo:
                                                 for movimento in movimentos:
                                                  arquivo.write(" ".join(map(str, movimento)) + "\n")

                                                  Função para reproduzir movimentos
                                                  def reproduzir_movimento(nome_arquivo):
                                                   try:
                                                    with open(nome_arquivo, "r") as arquivo:
                                                     movimentos = [list(map(int, linha.split())) for linha in arquivo.readlines()]
                                                      for movimento in movimentos:
                                                       for i, angulo in enumerate(movimento):
                                                        servos[i].set_angle(angulo)
                                                         time.sleep(1)  # Intervalo entre movimentos
                                                          except FileNotFoundError:
                                                           print("Arquivo não encontrado.")

                                                           Função principal
                                                           def main():
                                                            serial.Serial(PORTA_SERIAL, VEL_SERIAL).close()  # Fechar porta serial
                                                             while True:
                                                              print("1. Gravar movimento")
                                                               print("2. Reproduzir movimento")
                                                                escolha = input("Escolha: ")
                                                                 if escolha == "1":
                                                                  gravar_movimento()
                                                                   elif escolha == "2":
                                                                    nome_arquivo = input("Nome do arquivo: ")
                                                                     reproduzir_movimento(nome_arquivo)
                                                                      else:
                                                                       print("Opção inválida.")

                                                                       if __name__ == "__main__":
                                                                        main()
                                                                        ```

                                                                        Uso
                                                                        1. Conecte os servos à placa de controle.
                                                                        2. Abra o terminal e execute o script.
                                                                        3. Escolha opção 1 para gravar movimentos.
                                                                        4. Insira os ângulos para cada servo.
                                                                        5. Escolha opção 2 para reproduzir movimentos.
                                                                        6. Insira o nome do arquivo com os movimentos gravados.

                                                                        Observações
                                                                        - Ajuste a porta serial e velocidade conforme necessário.
                                                                        - Certifique-se de que os servos estejam conectados corretamente.
                                                                        - O código assume que os servos sejam do tipo "servo contínuo" sem limites de rotação.
                                                                        - O arquivo de movimentos é salvo no formato texto, com cada linha representando um movimento.