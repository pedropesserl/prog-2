#ifndef MOVE_H_
#define MOVE_H_

// Move o membro de nome member para imediatamente após o membro de nome target.
// Ambos devem existir em archive.
void move_member(char *archive_path, char *target, char *member);

#endif // MOVE_H_
