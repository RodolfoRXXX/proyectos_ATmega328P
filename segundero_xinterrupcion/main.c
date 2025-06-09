/*
    Programa que implementa un segundero utilizando el timer del microcontrolador ATmega328P
        Este segundero detalla el funcionamiento del timer del micro, configurando los registros
        destinados a ello.

        El segundero se realiza utilizando el registro de comparación A del timer 0 para generar
        una interrupción por comparación y devolver el timer a 0, el tiempo que se tarda en realizar
        esta interrupción se calcula en base a la frecuencia de trabajo configurada del micro
        y al período de tiempo que se desea que se genere la interrupción.asm
        Este timer se utiliza para hacer funcionar un LED de forma intermitente, durante cada período
        de tiempo elegido.

*/