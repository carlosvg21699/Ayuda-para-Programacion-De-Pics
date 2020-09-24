/******Nota importante*****
 * todas las funciones a continuacion son validas en el ide MPLAB
 * y funcionan con el pic 16f887
 * tomar esta informacion en cuenta en caso de usar un pic diferente
 * No se exactamente como detallar la licencia a si que hago constar en
 * estas lineas que este codigo pertenece a Mario Macario y Carlos 
 * Valdez quienes han  * codificado todas las funciones a continuación 
 * y permite su uso a todo aquel que las requiera bajo las condiciones 
 * y terminos que se describen a continuacion
 * Todas las funciones son completamente libres por lo que 
 * puedes copiar las que necesites y usarlas en cualquier tipo
 * de proyecto en el que las requieras con la una restriccion 
 * de contribuir con la comunidad. Si mejoras o creas alguna nueva
 * funcion a partir de las existente debes compartirla en este mismo
 * repositorio, asi como tambien podras agregar tu nombre 
 * para que la comunidad sepa que tu tambien contribuyes con ellos
 * para que todos podamos seguir creando cosas sorprendentes
 * sin necesidad de comenzar de 0.
 * el hecho de incumplir con esta condicion tendra concecuencias para
 * tu proyecto ya que el incumplimiento de la misma hara que el codigo
 * que te hayas llevado mejorado y modificado se convierta en plagio
 * o tambien podrias verte obligado a convertir tu proyecto terminado
 * en un proyecto 100% libre disponible sin ningun costo ni cobro para
 * todo aquel que desee utilizarlo.
 * *******************************************************************
 * Espero que todos colaboren a mejorar y hacer crecer este pequeño
 * proyecto, espero que tanto nosotros como los futuros colaboradores
 * podamos contribuir con todos ustedes facilitandoles la forma de
 * programar los pics utilizando lenguaje C.
 */ 


//-------------------------------------------------------------------------//
//-------------------- Funciones para delay -------------------------------//
//-------------------------------------------------------------------------//
void delay(int _tiempo,char _unidad)
{
    /***
     * Esta funcion reduce el delay a simplemente llamarlo
     * por medio dela funcion delay la cual recibe un parametro
     * numerico entero que sera el valor del tiempo
     * y el char unidad recibe la unidad de medida
     * en la que se tomarán los segundos
     * m = mili
     * u = micro
     * s = segundo
     ***/
    
    if(_unidad == 'm')
    {
        __delay_ms(_tiempo);
    }
    else if(_unidad == 'u')
    {
        __delay_us(_tiempo);
    }
    if(_unidad == 's')
    {
        __delay_ms(_tiempo*1000);
    }

}
void delaym(int _tiempo)
{
    __delay_ms(_tiempo);
}

void delayu(int _tiempo)
{
    __delay_us(_tiempo);
}

void delays(int _tiempo)
{
    __delay_ms(_tiempo*1000);
}
//-------------------------------------------------------------------------//
//-------------------- Funciones ADC --------------------------------------//
//-------------------------------------------------------------------------//
//estas dos funciones sirven para realizar lecturas analogas con
//el ADC
void iniciaAdc()
{
    /*los bits correspondientes a ADCS1 y ADCS0 se asignan
     * segun el resultado que se obtenga de la operación
     * (1/valor_del_cristal)*[2,8,32]
     * en esta operacion el valor del cristal dependera del que estemos
     * utilizando en este caso se calcula pra un cristal de 16Mhz
     * se debe multiplicar por cada uno de los valores hasta obtener
     * un resultado en micros(con micros me refiero a una notación
     * de valor x 10^-6 pueden tomarse como microsegundos "us") mayor
     * o igual a 1.6 us
     * en este caso nuestro mayor el numero con el que obtuvimos el resultado
     * deseado fue 32. Para asignar el valor usaremos los valores
     * predefinidos en la hoja de datos
     * 2   ->  00
     * 8   ->  01
     * 32  ->  10
     */
    ADCON0bits.ADCS1=1;
    ADCON0bits.ADCS0=0;
    /*esta linea nos sirve para encender adc, sin esta linea no
     * se podrian usar las conversines
     */
    ADCON0bits.ADON=1;
    /*puedes descomentar estas lineas para cambiar la alineacion 
     * del resultado que por defecto esta a la izquierda lo que hace
     * que el resultado de la conversión se pueda obtener por medio 
     * del ADRESH, cambiarlo a justificacion izquierda implicaría
     * utilizar ADRESL para obtener los resultados
     */
    //ADCON1bits.ADFM=1;
}
int lecturaAnalogica(int canal)
{
    /*en esta funcion se recibe el numero de canal que se desea
     * leer y se retorna el valor obtenido como resultado de la lectura
     * de dicho canal mediante la variable "readValue" de tipo int 
     * Puede elegir entre los canales analogicos del 0 al 15
     */
    int readValue;
    if(canal == 0)
    {
        ADCON0=0b10000011;
    }
    else if(canal == 1)
    {
        ADCON0=0b10000111;
    }
    else if(canal == 2)
    {
        ADCON0=0b10001011;
    }
    else if(canal == 3)
    {
        ADCON0=0b10001111;
    }
    else if(canal == 4)
    {
        ADCON0=0b10010011;
    }
    else if(canal == 5)
    {
        ADCON0=0b10010111;
    }
    else if(canal == 6)
    {
        ADCON0=0b10011011;
    }
    else if(canal == 7)
    {
        ADCON0=0b10011111;
    }
    else if(canal == 8)
    {
        ADCON0=0b10100011;
    }
    else if(canal == 9)
    {
        ADCON0=0b10100111;
    }
    else if(canal == 10)
    {
        ADCON0=0b10101011;
    }
    else if(canal == 11)
    {
        ADCON0=0b10101111;
    }
    else if(canal == 12)
    {
        ADCON0=0b10110011;
    }
    else if(canal == 13)
    {
        ADCON0=0b10110111;
    }
    else if(canal == 14)
    {
        ADCON0=0b10111011;
    }
    else if(canal == 15)
    {
        ADCON0=0b10111111;
    }
    while(ADCON0bits.GO_DONE==1);
    //return ADRESH;
    int aux = ADRESH;
    readValue = aux*10;
    aux = ADRESL;
    if(aux == 64)
    {
        readValue = readValue + 1;
    }
    else if(aux == 128)
    {
        readValue = readValue + 2;
    }
    else if(aux == 192)
    {
        readValue = readValue + 3;
    }
    return readValue;
}
//nota estas funciones permiten leer e imprimir un puerto analogico con ADC
//Inicio
void datos(char dato)
{    
    PORTCbits.RC0 = 1;
    PORTD = dato;
    habilitar_lectura();
    __delay_ms(2);
}
void controlar(int instruccion)
{
    PORTCbits.RC0 = 0;
    PORTD = instruccion;
    habilitar_lectura();
    __delay_ms(2);
}
void habilitar_lectura()
{
    PORTCbits.RC2 = 1;
    __delay_us(5);
    PORTCbits.RC2 = 0;
    __delay_us(5);
}
void init()
{
    TRISD = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC2 = 0;
    PORTCbits.RC2 = 0;
    PORTD = 0;
    __delay_ms(5);
    controlar(0b00111000);  ////Ancho de Bus, tamaño fuente, número de líneas
    controlar(0b00001111);  //Retroiluminación, cursor, parpadeo de cursor        
    controlar(1);   //Limpia Pantalla    
    controlar(2);   //Retorna el cursor
}
void ADC_print_LCD(int num)
{
    while(ADCON0bits.GO_DONE == 1);
        int adc = ADRESH;    
    controlar(1);
    controlar(128);
    for (int i = 0; i < 3; i++)
        datos(msj[i]);   
    datos(num + 48);        
    controlar(192);
    centena = adc / 100;
    decena = (adc % 100)/10;
    unidad = adc % 10;
    datos(centena + 48);
    datos(decena + 48);
    datos(unidad + 48);
    __delay_ms(1000);
}
//Fin

//funciones necesarias para imprimir en una lcd, tener en cuenta
//que las 4 funciones siguientes forman un grupo de funciones necesarias
// para poder trabajar con una lcd
void datos(char dato)
{
    PORTCbits.RC0 = 1;
    PORTD= dato;
    habilitar_lectura();
    __delay_ms(2);
    
}
void instrucciones(int instruccion)
{
    PORTCbits.RC0 = 0;
    PORTD= instruccion;
    habilitar_lectura();
    __delay_ms(2);
}

void habilitar_lectura()
{
    PORTCbits.RC2 = 1;
    __delay_us(5);
    PORTCbits.RC2 = 0;
    __delay_us(5);
}

void inicializar()
{
    TRISD=0;    
    TRISCbits.TRISC0=0;
    TRISCbits.TRISC2=0;
    PORTCbits.RC2=0;
    PORTD=0;
    __delay_ms(5);
    instrucciones(0b00111100); //Configuracion ancho de bus, número de líneas y tamaño de fuente
    instrucciones(15);         //Habilitacion de display(Retroiluminación), mostrar cursor y parpadeo del cursor   
    instrucciones(1);          //Limpieza de pantalla
    instrucciones(2);          //Retornar  el cursor
}

