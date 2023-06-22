#ifndef MOVE_H_
#define MOVE_H_

// Move o membro de nome member para imediatamente após o membro de nome target,
// que deve existir em archive. Se member não estiver no archive, insere após target.
void move_member(char *archive_path, char *target, char *member);

#endif // MOVE_H_
