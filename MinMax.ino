#include <Keypad.h>
#include <LiquidCrystal.h>
bool Jeufini= false;
int allumettes = 21;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 33, 35, 37}; //connect to the column pinouts of the keypad
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//initialize an instance of class NewKeypad

int minMax(int allumettes,int joueur){
  if (allumettes == 0)
  {
    if (joueur == 1)
    {
      return 1;// j'ai swap les deux donc l'ordi pensait que si le joeur gagnait gagner la partie, il était recompensé donc il faisait toujours la plus petite somme 1 à chaque fois pour atteindre 0 et perdre
    }
    else  
    {
      return -1;
    }
  }
  if(joueur == 1)
  {
    int max_eval= -1000;
    for(int i=1;i<=3;i++)
    {
      if(allumettes - i >= 0)
      {
        int eval = minMax(allumettes-i,2);

        if (eval > max_eval) {
          max_eval = eval;
        }
      }
    }
    return max_eval;
    
  }
  else 
  {

    int min_eval= 1000;
    for(int i=1;i<=3;i++)
    {
      if(allumettes - i >= 0)
      {
        int eval = minMax(allumettes-i,1);

        if (eval < min_eval) {
          min_eval = eval;
        }
      }
    }
    return min_eval;
    
  }

}

int retourMeilleurMouv(int allumettes)
{
  int meilleur_mouv=1;
   int meilleur_valeur= -1000;
   for(int i=1;i<=3;i++)
    {
      if(allumettes-i>=0)
      {
        int valeur = minMax(allumettes-i,2);
        if (valeur>meilleur_valeur)
        {
          meilleur_valeur= valeur;
          meilleur_mouv= i;
        }
      }

    }
    return meilleur_mouv;
}


Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("jeu allumettes");
  delay(2000);
  lcd.clear();
  lcd.print("Nn allumettes 21");
  lcd.setCursor(0,1);
  lcd.print("à ton tour");

}

void loop() {
  if (Jeufini) return;

  char key = customKeypad.getKey();

  if (key) {
    // Le joueur choisit seulement 1, 2 ou 3
    if (key == '1' || key == '2' || key == '3') {
      int choix = key - '0';
      allumettes -= choix;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tu prends ");
      lcd.print(choix);
      lcd.print(" ");

      lcd.setCursor(0, 1);
      lcd.print("Restant: ");
      lcd.print(allumettes);

      delay(1500);

      if (allumettes <= 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tu as perdu !");
        Jeufini = true;
        return;
      }

      // Tour de l’ordi
      int mouv = retourMeilleurMouv(allumettes);
      allumettes -= mouv;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ordi prend ");
      lcd.print(mouv);

      lcd.setCursor(0, 1);
      lcd.print("Restant: ");
      lcd.print(allumettes);

      delay(1500);

      if (allumettes <= 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ordi a perdu !");
        Jeufini = true;
        return;
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ton tour !");
      lcd.setCursor(0, 1);
      lcd.print("Choisis 1-3");
    }
  }
   
}
