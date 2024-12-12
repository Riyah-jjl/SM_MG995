#include <Arduino.h>

/*
Commande Servo Moteur MG 995

Programme Basique sur Arduino Mega.
IDE Arduino 2.3.3

Constituants :
- Servo moteur MG 995
- Potentiomètre 10 KOhm

version 1 : octobre 2024
*/

// --- Inclusion des bibliothèques
// -- Librairie Servo.h à télécharger le cas échéant.
#include <Servo.h>

// - Déclaration des variables et autres objets.

Servo myServo; // creation de l'objet servo appelable sous le nom "myservo"

int const potPin = A0; // Le curseur du potentiomètre est connecté à la broche analogique Al de l'Arduino.
int potVal;            // variable de la position du curseur après conversion numérique [10 à 1023] 10 bits.
int angle;             // variable de fixation de l'angle axe moteur.

int const Angle_Mini = 0; // fixe la borne inférieure de la variation angulaire de l'axe moteur.
int const Angle_Max = 179;// fixe la borne supérieure de la variation angulaire de l'axe moteur.

// --- Configuration

void setup () {

myServo.attach(3);    // fonction déclarant que la Mli du servo est connectée la broche digitale 3.
Serial.begin(9600);  // Initialisation de la liaison série PC ‹---> Arduino.

}

// --- Boucle d'exécution.

void loop () {

Serial.println("");
Serial.println("Nouvelle commande d'angle !! ");


Serial.println(""); // -- Lecture de la commande angulaire.

potVal = analogRead (potPin); // lecture de la valeur du potentiomètre.

Serial.print("Valeur du potentiomètre : "); // Affichage à des fins de contrôle de celle-ci sur le moniteur série.

Serial.print(potVal);

// -- Mise à l'échelle de la valeur angulaire proportionnellement à l'amplitude de la conversion numérique.

angle = map (potVal, 0, 1023, Angle_Mini, Angle_Max);

/* la valeur de la variable "potVal" comprise entre 0 et 1023 (10 bits)
est transposée linéairement en un angle compris entre e et 179 °. une valeur @ du potentiomètre implique un angle de 0° une valeur de 1023 implique une valeur d'angle de 179°
une valeur de 1 du potentiomètre implique une valeur d'angle de
(1/1023)*179° soit env 0,175°
si vous souhaitez réduire l'amplitude angulaire du mouvement, changer les
valeurs de : Angle Mini et Angle Max.
Attention vous devez être dans l'intervalle [ 0 ; 179 ] sinon Les butées de protection vous empêchent d'aller au-delà mais votre fonctionnement est en mode dégradé */

// -- Affichage de l'angle demandé.
Serial.print(", angle: ");
Serial.println(angle);

// -- Application de la commande position au servo moteur.

myServo.write(angle); // fonction appartenant à la bibilothèque "servo" qui applique la commande de position.

// -- Attente de boucle.

delay(5000);
}