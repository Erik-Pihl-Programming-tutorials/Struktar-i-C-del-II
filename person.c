/********************************************************************************
* person.c: Inneh�ller definitioner av associerade funktioner tillh�rande
*           strukten person, som anv�nds f�r agring samt utskrift av persondata.
********************************************************************************/
#include "person.h"

/* Statiska funktioner: */
struct person_vtable* person_vtable_ptr_new(void);

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
                 const enum gender gender)
{
   self->name = name;
   self->age = age;
   self->address = address;
   self->occupation = occupation;
   self->gender = gender;
   self->vptr = person_vtable_ptr_new();
   return;
}

/********************************************************************************
* person_clear: Nollst�ller persondata lagrat av angivet person-objekt.
*
*               - self: Pekare till objektet som ska nollst�llas.
********************************************************************************/
void person_clear(struct person* self)
{
   self->name = 0;
   self->age = 0;
   self->address = 0;
   self->occupation = 0;
   self->gender = GENDER_NONE;
   self->vptr = 0;
   return;
}

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
                          const enum gender gender)
{
   struct person* self = (struct person*)malloc(sizeof(struct person));
   if (!self) return 0;
   person_init(self, name, age, address, occupation, gender);
   return self;
}

/********************************************************************************
* person_delete: Raderar angivet person-objekt genom att frig�ra dynamiskt
*                allokerat minne f�r denna och s�tter motsvarande pekare till
*                null. F�r att m�jligg�ra detta passeras adressen till den pekare 
*                som pekar p� det dynamiskt allokerade minnet.
*
*                - self: Adressen till den pekare som pekar p� objektet som
*                        som ska raderas.
********************************************************************************/
void person_delete(struct person** self)
{
   free(*self);
   *self = 0;
   return;
}

/********************************************************************************
* person_print: Skriver ut lagrad persondata via angiven utstr�m, d�r
*               standardutenheten stdout anv�nds som default f�r utskrift
*               i terminalen.
*
*               - self   : Pekare till objektet som lagrar persondatan.
*               - ostream: Pekare till angiven utstr�m (default = stdout).
********************************************************************************/
void person_print(const struct person* self,
                  FILE* ostream)
{
   if (!ostream) ostream = stdout;
   fprintf(ostream, "--------------------------------------------------------------------------------\n");
   fprintf(ostream, "Name: %s\n", self->name);
   fprintf(ostream, "Age: %u\n", self->age);
   fprintf(ostream, "Address: %s\n", self->address);
   fprintf(ostream, "Occupation: %s\n", self->occupation);
   fprintf(ostream, "Gender: %s\n", person_gender_str(self));
   fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
   return;
}

/********************************************************************************
* person_gender_str: Returnerar personens k�n p� textform.
*
*                    - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_gender_str(const struct person* self)
{
   if (self->gender == GENDER_MALE) return "Male";
   else if (self->gender == GENDER_FEMALE) return "Female";
   else if (self->gender == GENDER_OTHER) return "Other";
   else return "Unspecified";
}

/********************************************************************************
* person_vtable_ptr_new: Returnerar en pekare till ett vtable inneh�llande
*                        funktionspekare till associerade funktioner f�r
*                        strukten person. Tabellen deklareras statiskt s� att
*                        minnet f�r den kvarst�r hela programmet. Pekarna s�tts
*                        till att peka p� motsvarande funktioner vid start.
*                        Vid anrop av denna funktion returneras sedan en pekare
*                        till denna tabell.
********************************************************************************/
struct person_vtable* person_vtable_ptr_new(void)
{
   static struct person_vtable self = 
   {
      .print = &person_print,
      .gender_str = &person_gender_str,
      .clear = &person_clear
   };

   return &self;
}