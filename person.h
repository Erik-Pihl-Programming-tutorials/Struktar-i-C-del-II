/********************************************************************************
* person.h: Inneh�ller funktionalitet f�r lagring samt utskrift av persondata
*           via strukten person samt associerade funktioner.
********************************************************************************/
#ifndef PERSON_H_
#define PERSON_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>  /* Inneh�ller funktionalitet f�r utskrift och inmatning. */
#include <stdlib.h> /* Inneh�ller funktionalitet f�r dynamisk minnesallokering. */

/********************************************************************************
* gender: Enumeration f�r val av k�n.
********************************************************************************/
enum gender
{
   GENDER_MALE,   /* Man. */
   GENDER_FEMALE, /* Kvinna. */
   GENDER_OTHER,  /* �vrigt. */
   GENDER_NONE    /* Ospecificerat. */
};

/********************************************************************************
* person: Strukt f�r lagring samt utskrift av persondata.
********************************************************************************/
struct person
{
   const char* name;                 /* Personens namn. */
   unsigned int age;                 /* Personens �lder. */
   const char* address;              /* Personens hemadress. */
   const char* occupation;           /* Personens yrke. */
   enum gender gender;               /* Personens k�n. */
   const struct person_vtable* vptr; /* Pekare till vtable inneh�llande funktionspekare. */
};

/********************************************************************************
* person_vtable: Strukt f�r vtable (virtuell tabell) inneh�llande adresser till 
*                associerade funktioner f�r strukten person.
********************************************************************************/
struct person_vtable
{
   /********************************************************************************
   * print: Skriver ut lagrad persondata via angiven utstr�m, d�r standardutenheten
   *        stdout anv�nds som default f�r utskrift i terminalen.
   *
   *        - self   : Pekare till objektet som lagrar persondatan.
   *        - ostream: Pekare till angiven utstr�m (default = stdout).
   ********************************************************************************/
   void (*print)(const struct person* self,
                 FILE* ostream);

   /********************************************************************************
   * gender_str: Returnerar personens k�n p� textform.
   *
   *             - self: Pekare till objektet som lagrar persondatan.
   ********************************************************************************/
   const char* (*gender_str)(const struct person* self);

   /********************************************************************************
   * clear: Nollst�ller persondata lagrat av angivet person-objekt.
   *
   *        - self: Pekare till objektet som ska nollst�llas.
   ********************************************************************************/
   void (*clear)(struct person* self);
};

/********************************************************************************
* person_init: Lagrar angiven persondata i ett person-objekt.
* 
*              - self      : Pekare till objektet som ska lagra uppgifterna.
*              - name      : Personens namn.
*              - age       : Personens �lder.
*              - address   : Personens hemadress.
*              - occupation: Personens yrke.
*              - gender    : Personens k�n.
********************************************************************************/
void person_init(struct person* self, 
                 const char* name,
                 const unsigned int age,
                 const char* address,
                 const char* occupation,
                 const enum gender gender);

/********************************************************************************
* person_clear: Nollst�ller persondata lagrat av angivet person-objekt.
* 
*               - self: Pekare till objektet som ska nollst�llas.
********************************************************************************/
void person_clear(struct person* self);

/********************************************************************************
* person_new: Allokerar minne och lagrar angiven persondata i ett person-objekt.
*             En pekare till det dynamiskt allokerade objektet returneras.
*             Om minnesallokeringen misslyckas s� returneras null.
*
*             - name      : Personens namn.
*             - age       : Personens �lder.
*             - address   : Personens hemadress.
*             - occupation: Personens yrke.
*             - gender    : Personens k�n.
********************************************************************************/
struct person* person_new(const char* name,
                          const unsigned int age,
                          const char* address,
                          const char* occupation,
                          const enum gender gender);

/********************************************************************************
* person_delete: Raderar angivet person-objekt genom att frig�ra dynamiskt 
*                allokerat minne f�r denna och s�tter motsvarande pekare till null. 
*                F�r att m�jligg�ra detta passeras adressen till den pekare som 
*                pekar p� det dynamiskt allokerade minnet.
*
*                - self: Adressen till den pekare som pekar p� objektet som
*                        som ska raderas.
********************************************************************************/
void person_delete(struct person** self);

/********************************************************************************
* person_print: Skriver ut lagrad persondata via angiven utstr�m, d�r 
*               standardutenheten stdout anv�nds som default f�r utskrift
*               i terminalen.
*
*               - self   : Pekare till objektet som lagrar persondatan.
*               - ostream: Pekare till angiven utstr�m (default = stdout).
********************************************************************************/
void person_print(const struct person* self,
                  FILE* ostream);

/********************************************************************************
* person_gender_str: Returnerar personens k�n p� textform.
* 
*                    - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_gender_str(const struct person* self);

#endif /* PERSON_H_ */