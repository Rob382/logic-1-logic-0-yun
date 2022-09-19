void leer_1_entrada(){
// este ejemplo de uso proviene de un proyecto que yo realicé para una empresa
// esta sección del proyecto requería diferenciar tres estados distintos en una misma entrada con el ATtiny85

// los distintos estados eran:
// pánel armado = 0 lógico
// pánel desarmado = 1 lógico
// estado de alarma = tren de pulsos

// el tiempo umbrál se declara en cada condiciónante "if" por separado en caso de que se requiera tiempos asíncronos

///////////////// NOTA IMPORTANTE /////////////////////
// este programa fue realizado con un microcontrolador attiny85
// para poder monitorizar por medio de comunicación serial se requirió conectar a un arduino yun y enviar esos datos por medio del wifi
// esto significa que todas las instancias para imprimir por consola serial en lugar de escribirse como "Serial.println();" cambian a "Console.println();"
// en caso de probarlo en cualquier otra placa arduino conectada directamente mediante cable usb es necesario lo siguiente:
//  - Borrar o comentar los llamamientos a librerias al incio del programa
//  - Borrar o comentar las lineas "Bridge.begin();" y "Console.begin();" dentro del "void setup(){}"
//  - Remplazar todoas las lineas que tienen escrito "Console.println" con "Serial.println" utilizando el atajo CTRL+F



// si se requiere usar solo una salida del panel CNord se puede conectar solamente la entrada 2 como notificador
// pero a costa de usar solo una salida se verá un retraso de 6 segundos en la detección de estados del panel

if (currentMillis - pulsacion_previa > 50){
  byte entrada1 = digitalRead(4);

  if(entrada1 == LOW && entrada_1_prev == HIGH && duracion_1_logico < 3200){
//    Console.println("short 1 logico");
    contador_pulsaciones = contador_pulsaciones+1;
    logico_1_pulso_largo_prev = false;
    logico_0_pulso_largo_prev = false;
  }
  if(entrada1 == HIGH && entrada_1_prev == LOW && duracion_0_logico < 3200){
//    Console.println("short 0 logico");
    contador_pulsaciones = contador_pulsaciones+1;
    logico_1_pulso_largo_prev = false;
    logico_0_pulso_largo_prev = false;
  }
  
  if(entrada1 == HIGH && entrada_1_prev == LOW){
    logico_1_largo = currentMillis;
//    Console.println("1 logico pulsado"); 
    entrada_1_prev = HIGH; 
  }
  
  if(entrada1 == LOW && entrada_1_prev == HIGH){
    logico_0_largo = currentMillis;
//    Console.println("0 logico pulsado");  
    entrada_1_prev = LOW;
  }
  
  duracion_1_logico = currentMillis - logico_1_largo;
  duracion_0_logico = currentMillis - logico_0_largo;
  
  if (entrada1 == HIGH && logico_1_pulso_largo_prev == false && duracion_1_logico >= 3200){
//    Console.println("1 logico pulsacion larga");
// aquí se configura que sucede al ser "1 logico pulsacion larga"
    logico_1_pulso_largo_prev = true;
    logico_0_pulso_largo_prev = false;
    armado = false;
    desarmado = true;
    alarma = false;
    tonoactivado = false;
    contadortono = 0;
    contador_pulsaciones = 0;
    sirena_activada_por_pulsos = false;
    digitalWrite(2, LOW);             //apaga la sirena (claxón)
//    digitalWrite(5, LOW);             //apaga la bocina
  
  }
  if (entrada1 == LOW && logico_0_pulso_largo_prev == false && duracion_0_logico >= 3200){
    logico_1_pulso_largo_prev = false;
    logico_0_pulso_largo_prev = true;
    //Console.println("0 logico pulsacion larga");
//    aquí se configura que sucede al ser un "0 logico pulsacion larga"
    armado = true;
    desarmado = false;
    alarma = false;
    tonoactivado = false;
    contadortono = 0;
    contador_pulsaciones = 0;
    sirena_activada_por_pulsos = false;
    digitalWrite(2, LOW);             //apaga la sirena (claxón)
//    digitalWrite(5, LOW);             //apaga la bocina
  
  }

// aquí se configura que sucede al ser un tren de pulsos
  if (contador_pulsaciones >= 4 && sirena_activada_por_pulsos == false){
    alarma = true;
    armado = false;
    desarmado = false;
    sirena_activada_por_pulsos = true;
  }

  if (contador_pulsaciones >= 200){
    contador_pulsaciones = 0;
  }
  
  pulsacion_previa = currentMillis;
}
}
