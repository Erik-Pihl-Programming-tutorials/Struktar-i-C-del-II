/********************************************************************************
* person.c: Innehåller definitioner av associerade funktioner tillhörande
*           strukten person, som används för agring samt utskrift av persondata.
********************************************************************************/
#include "person.h"

/* Statiska funktioner: */
struct person_vtable* person_vtable_ptr_new(void);

/********************************************************************************
* person_init: Lagrar angiven persondata i ett person-objekt.
*
*              - self      : Pekare till objektet som ska lagra uppgifterna.
*              - name      : Personens namn.
*              - age       : Personens ålder.
*              - address   : Personens hemadress.
*              - occupation: Personens yrke.
*              - gender    : Personens kön.
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
* person_clear: Nollställer persondata lagrat av angivet person-objekt.
*
*               - self: Pekare till objektet som ska nollställas.
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
*             Om minnesallokeringen misslyckas så returneras null.
*
*             - name      : Personens namn.
*             - age       : Personens ålder.
*             - address   : Personens hemadress.
*             - occupation: Personens yrke.
*             - gender    : Personens kön.
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
* person_delete: Raderar angivet person-objekt genom att frigöra dynamiskt
*                allokerat minne för denna och sätter motsvarande pekare till
*                null. För att möjliggöra detta passeras adressen till den pekare 
*                som pekar på det dynamiskt allokerade minnet.
*
*                - self: Adressen till den pekare som pekar på objektet som
*                        som ska raderas.
********************************************************************************/
void person_delete(struct person** self)
{
   free(*self);
   *self = 0;
   return;
}

/********************************************************************************
* person_print: Skriver ut lagrad persondata via angiven utström, där
*               standardutenheten stdout används som default för utskrift
*               i terminalen.
*
*               - self   : Pekare till objektet som lagrar persondatan.
*               - ostream: Pekare till angiven utström (default = stdout).
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
* person_gender_str: Returnerar personens kön på textform.
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
* person_vtable_ptr_new: Returnerar en pekare till ett vtable innehållande
*                        funktionspekare till associerade funktioner för
*                        strukten person. Tabellen deklareras statiskt så att
*                        minnet för den kvarstår hela programmet. Pekarna sätts
*                        till att peka på motsvarande funktioner vid start.
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