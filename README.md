# logic-1-logic-0-yun
Obtener 4 estados distintos de un solo pulsador  o un tren de pulsos (1 lógico corto, 1 lógico largo, 0 lógico corto, 0 lógico largo).

***Programa realizado para ardúino yun con monitor serial por medio de wifi***

Este programa distinge 4 estados distintos en un único pulsador:
- logic 1 short al haber sido presionado el pulsador durante el tiempo menor al establecido como umbrál.
- logic 1 long al haber sido presionado el pulsador durante el tiempo mayor al establecido como umbrál (despues de pasado el tiempo úmbral al mantenerlo presionado no se repite la acción hasta que cambie de estado lógico).
- logic 0 short al haber sido soltado el pulsador durante un tiempo menor al úmbral (se suelta y se vuelve a presionar el pulsador antes del tiempo umbrál).
- logic 0 long al haber sido soltado el pulsador durante más del tiempo umbrál programado.

*Para fácil entendimiento se puede utilizar para diferenciar si en el mismo interruptor/entrada está recibiendo un tren de pulsos con periodo igual al doble del tiempo umbrál o se mantiene en un estado 1 lógico o 0 lógico constante.*

*Revizar el ejemplo de uso.*
