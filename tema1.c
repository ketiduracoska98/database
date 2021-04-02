#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "header.h"

//KETI DURACOSKA 322CB

// Allocate memory for database
t_db* INIT_DB(char* db_name) {
	t_db* database = malloc(sizeof(t_db));
	if(database == NULL) {
		return NULL;
	}
	database->tables = NULL;
	strcpy(database->name, db_name);
	return database;
}

// Checks if the table already exist in database
int exist_table(t_table *tables, char *line_sep[20]) {
	int found = 0;
	while(tables != NULL) {
		// line_sep[0] holds the table name
		if(strcmp(line_sep[0], tables->name) == 0) {
			found = 1;
		}
		tables = tables->next;
	}
	return found;
}

// Create the table and add it to tables list
t_table* creat_table(t_table **head_ref, char *line_sep[20]) {
	t_table *head = *head_ref;
	t_table *table_node = malloc(sizeof(t_table));
	if(table_node == NULL) {
		return NULL;
	}
	table_node->next = NULL;
	strcpy(table_node->name, line_sep[0]);
	// line_sep[1] holds the data type
	if(strcmp(line_sep[1], "STRING") == 0) {
		table_node->type = STRING;
	}
	else if(strcmp(line_sep[1], "INT") == 0) {
		table_node->type = INT;
	}
	else if(strcmp(line_sep[1], "FLOAT") == 0) {
		table_node->type = FLOAT;
	}
	else {
		printf("Unknown data type \"%s\".\n", line_sep[1]);
	}
	table_node->columns = NULL;
	table_node->lines = NULL;
	
	if(*head_ref == NULL) {
		*head_ref = table_node;
		return *head_ref;
	}
	while(head->next != NULL) {
		head = head->next; 
	}
	head->next = table_node;
	return *head_ref;
}

// Create list of columns 
t_column* create_column(int n, char *line_sep[20]) {
	int i = 0;
	t_column *head = NULL, *temp = NULL, *p = NULL;
	for(i = 0; i < n; i++) {
		temp = malloc(sizeof(t_column));
		if(temp == NULL) {
			return NULL;
		}
		temp->next = NULL;
		strcpy(temp->name, line_sep[i+2]);
		if(head == NULL) {
			head = temp;
		}
		else {
			p = head;
			while(p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
		}
	}
	return head;
}

// Create a cell of type string
t_stringCell* createS_cell(int n, char *line_sep[20]) {
	int i = 0;
	t_stringCell *head = NULL, *temp = NULL, *p = NULL; 
	for(i = 0; i < n; i++) {
		temp = malloc(sizeof(t_stringCell));
		if(temp == NULL) {
			return NULL;
		}
		temp->next = NULL;
		// alocate memory for char *value
		temp->value = malloc(sizeof(char) * strlen(line_sep[i]) + 1);
		if(temp->value == NULL) {
			return NULL;
		}
		strcpy(temp->value, line_sep[i]);
		if(head == NULL) {
			head = temp;
		}
		else {
			p = head;
			while(p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
		}
	}
	return head;
}

// Create a line of cells of type string
t_stringLine* create_stringLine(void **head_ref, int n, char *line_sep[20]) {
	t_stringLine *head = *head_ref;
	t_stringLine *line_node = (t_stringLine *)malloc(sizeof(t_stringLine));
	if(line_node == NULL) {
		return NULL;
	}
	line_node->next = NULL;
	line_node->cells = createS_cell(n, line_sep);
	if(line_node->cells == NULL) {
		return NULL;
	}

	if(*head_ref == NULL) {
		*head_ref = line_node;
		return *head_ref;
	}
	while(head->next != NULL) {
		head = head->next;
	}
	head->next = line_node;
	return *head_ref;
}

// Create a cell of type float
t_floatCell* createF_cell(int n, char *line_sep[20]) {
	int i = 0;
	t_floatCell *head = NULL, *temp = NULL, *p = NULL; 
	for(i = 0; i < n; i++) {
		temp = malloc(sizeof(t_floatCell));
		if(temp == NULL) {
			return NULL;
		} 
		temp->next = NULL;
		temp->value = atof(line_sep[i]);
		if(head == NULL) {
			head = temp;
		}
		else {
			p = head;
			while(p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
		}
	}
	return head;
}

// Create a line of cells of type float
t_floatLine* create_floatLine(void **head_ref, int n, char *line_sep[20]) {
	t_floatLine *head = *head_ref;
	t_floatLine *line_node = (t_floatLine *)malloc(sizeof(t_floatLine));
	line_node->next = NULL;
	line_node->cells = createF_cell(n, line_sep);
	if(line_node->cells == NULL) {
		return NULL;
	}
	if(*head_ref == NULL) {
		*head_ref = line_node;
		return *head_ref;
	}
	while(head->next != NULL) {
		head = head->next;
	}
	head->next = line_node;
	return *head_ref;
}

// Create a cell of type int
t_intCell* createI_cell(int n, char *line_sep[20]) {
	int i = 0;
	t_intCell *head = NULL, *temp = NULL, *p = NULL; 
	for(i = 0; i < n; i++) {
		temp = malloc(sizeof(t_intCell));
		if(temp == NULL) {
			return NULL;
		}
		temp->next = NULL;
		temp->value = atoi(line_sep[i]);
		if(head == NULL) {
			head = temp;
		}
		else {
			p = head;
			while(p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
		}
	}
	return head;
}

// Create a line of cells of type int
t_intLine* create_intLine(void **head_ref, int n, char *line_sep[20]) {
	t_intLine *head = *head_ref;
	t_intLine *line_node = (t_intLine *)malloc(sizeof(t_intLine));
	line_node->next = NULL;
	line_node->cells = createI_cell(n, line_sep);
	if(line_node->cells == NULL) {
		return NULL;
	}
	if(*head_ref == NULL) {
		*head_ref = line_node;
		return *head_ref;
	}
	while(head->next != NULL) {
		head = head->next;
	}
	head->next = line_node;
	return *head_ref;
}

// Calculate a number of digits
unsigned int number_of_digits(int n) {
	unsigned int count = 0;
	if(n == 0) {
		return 1;
	}
	while(n != 0) {
		n /= 10;
		count++;
	}
	return count;
}

// Print table
void print_table(t_table *tables, char *name) {
	unsigned int i, j, columns_num = 0, found_table = 0;
	while(tables != NULL) {
		// search for the table you want to print 
		if(strcmp(name,tables->name) == 0) {
			found_table++;
			columns_num = 0;
			printf("TABLE: %s\n", tables->name);
			t_column *column = tables->columns;
			// print all the columns
			while(column != NULL) {
				columns_num++;
				printf("%s",column->name);
				for(i = 0; i <= (30 - strlen(column->name)); i++) {
					printf(" ");
				}
				column = column->next;
			}
			printf("\n");
			for(j = 0; j < columns_num; j++) {
				for(i = 0; i < 30; i++) {
					printf("-");
				}
				printf(" ");
			}
			printf("\n");
				if(tables->type == 0) {
					// print cells of type integer
					t_intLine *line = (t_intLine *)tables->lines;
					while(line != NULL) {
						t_intCell *cell = line->cells;
						while(cell != NULL) {
							printf("%d",cell->value);
							for(i = 0; i <= 
							(30 - number_of_digits(cell->value)); i++) {
								printf(" ");
							}
							cell = cell->next;
						}
						printf("\n");
						line = line->next;
					}
				}
				else if(tables->type == 1) {
					// print cells of type float
					t_floatLine *line = (t_floatLine *)tables->lines;
					while(line != NULL) {
						t_floatCell *cell = line->cells;
						while(cell != NULL) {
							printf("%f",cell->value);
							for(i = 0; i <= 
							(30 - number_of_digits((int)cell->value) - 7); i++) {
								printf(" ");
							}
							cell = cell->next;
						}
						printf("\n");
						line = line->next; 
					}
				}
				else if(tables->type == 2) {
					// print cells of type string
					t_stringLine *line = (t_stringLine *)tables->lines;
					while(line != NULL) {
						t_stringCell *cell = line->cells;
						while(cell != NULL) {
							printf("%s",cell->value);
							for(i = 0; i <= (30 - strlen(cell->value)); i++) {
								printf(" ");
							}
							cell = cell->next;
						}
						printf("\n");
						line = line->next;
					}
				}
			printf("\n");
		}
		tables = tables->next;
	}
	if(found_table == 0) {
		printf("Table \"%s\" not found in database.\n", name);
	}
}

// Print whole database
void PRINT_DB(t_db *database) {
	printf("DATABASE: %s\n\n", database->name);
	t_table *tables = database->tables;
	// print all the tables
	while(tables != NULL) {
		print_table(tables,tables->name);
		tables = tables->next;
	}
}

// Print all the tables wihout the cells
void print_columns(t_table *tables, char *name) {
	unsigned int i, j, columns_num = 0;
	while(tables != NULL) {
		if(strcmp(name,tables->name) == 0) {
			columns_num = 0;
			printf("TABLE: %s\n", tables->name);
			t_column *column = tables->columns;
			while(column != NULL) {
				columns_num++;
				printf("%s",column->name);
				for(i = 0; i <= (30 - strlen(column->name)); i++) {
					printf(" ");
				}
				column = column->next;
			}
			printf("\n");
			for(j = 0; j < columns_num; j++) {
				for(i = 0; i < 30; i++) {
					printf("-");
				}
				printf(" ");
			}
			printf("\n\n");
		}
		tables = tables->next;
	}
}

// Print the lines for which the condition is true 
void print_lines(t_table *tables,char *tb_name, char *cl_name, 
	char *relation, char* value) {
	int  relation_index = 0, found_column = 0, column_index = 0;
	int  j, relation_found = 0;
	unsigned int i;
	while(tables != NULL) {
		column_index = 0;
		// find the table
		if(strcmp(tb_name, tables->name) == 0) {
			printf("TABLE: %s\n",tables->name );
			t_column *columns = tables->columns;
			while(columns != NULL) {
				column_index++;
				printf("%s",columns->name);
				for(i = 0; i <= (30 - strlen(columns->name)); i++) {
					printf(" ");
				}
				// find the column for which comparing will be done
				if(strcmp(cl_name, columns->name) == 0) {
					found_column++;
				}
				// and index of that column
				if(found_column == 0) {
					relation_index++;
				}
				columns = columns->next;
			}
			printf("\n");
			for(j = 0; j < column_index; j++) {
				for(i = 0; i < 30; i++) {
					printf("-");
				}
				printf(" ");
			}
				int index;
				// integer type
				if(tables->type == 0) {
					t_intLine *line = (t_intLine *)tables->lines;
					// go next until the cell you need to compare
					while(line != NULL) {
						index = relation_index;
						t_intCell *int_cell = line->cells;
						while(index != 0) {
							index--;
							int_cell = int_cell->next;
						}
						// find the relation operator
						if(strcmp(relation, "<") == 0) {
							// check if it's true
							if(int_cell->value < atoi(value)) {
								relation_found++;
								printf("\n");
								t_intCell *cell = line->cells;
								// print the cells value
								while(cell != NULL) {
									printf("%d", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, "<=") == 0) {
							if(int_cell->value <= atoi(value)) {
								relation_found++;
								printf("\n");
								t_intCell *cell = line->cells;
								while(cell != NULL) {
									printf("%d", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(int_cell->value == atoi(value)) {
								relation_found++;
								printf("\n");
								t_intCell *cell = line->cells;
								while(cell != NULL) {
									printf("%d", cell->value);
									for(i = 0; i <=
									(30 - number_of_digits(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, "!=") == 0) {
							if(int_cell->value != atoi(value)) {
								relation_found++;
								printf("\n");
								t_intCell *cell = line->cells;
								while(cell != NULL) {
									printf("%d", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(int_cell->value >= atoi(value)) {
								relation_found++;
								printf("\n");
								t_intCell *cell = line->cells;
								while(cell != NULL) {
									printf("%d", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, ">") == 0) {
							if(int_cell->value > atoi(value)) {
								relation_found++;
								printf("\n");
								t_intCell *cell = line->cells;
								while(cell != NULL) {
									printf("%d", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						line = line->next;
					}
				}
					// same procedure for float
					if(tables->type == 1) {
					t_floatLine *line = (t_floatLine *)tables->lines;
					while(line != NULL) {
						index = relation_index;
						t_floatCell *float_cell = line->cells;
						while(index != 0) {
							index--;
							float_cell = float_cell->next;
						}
						if(strcmp(relation, "<") == 0) {
							if(float_cell->value < atof(value)) {
								relation_found++;
								printf("\n");
								t_floatCell *cell = line->cells;
								while(cell != NULL) {
									printf("%f", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits((int)cell->value) 
									- 7); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, "<=") == 0) {
							if(float_cell->value <= atof(value)) {
								relation_found++;
								printf("\n");
								t_floatCell *cell = line->cells;
								while(cell != NULL) {
									printf("%f", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits((int)cell->value) 
									- 7); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(float_cell->value == atof(value)) {
								relation_found++;
								printf("\n");
								t_floatCell *cell = line->cells;
								while(cell != NULL) {
									printf("%f", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits((int)cell->value)
									- 7); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation,"!=") == 0) {
							if(float_cell->value != atof(value)) {
								relation_found++;
								printf("\n");
								t_floatCell *cell = line->cells;
								while(cell != NULL) {
									printf("%f", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits((int)cell->value) 
									- 7); i++) {
										printf(" ");
									}
									cell = cell->next;
								};
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(float_cell->value >= atof(value)) {
								relation_found++;
								printf("\n");
								t_floatCell *cell = line->cells;
								while(cell != NULL) {
									printf("%f", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits((int)cell->value) 
									- 7); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, ">") == 0) {
							if(float_cell->value > atof(value)) {
								relation_found++;
								printf("\n");
								t_floatCell *cell = line->cells;
								while(cell != NULL) {
									printf("%f", cell->value);
									for(i = 0; i <= 
									(30 - number_of_digits((int)cell->value) 
									- 7); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						line = line->next;
					}
				}
				// same procedure for int
					if(tables->type == 2) {
					t_stringLine *line = (t_stringLine *)tables->lines;
					while(line != NULL) {
						index = relation_index;
						t_stringCell *string_cell = line->cells;
						while(index != 0) {
							index--;
							string_cell = string_cell->next;
						}
						if(strcmp(relation, "<") == 0) {
							if(strcmp(string_cell->value, value) < 0) {
								relation_found++;
								printf("\n");
								t_stringCell * cell = line->cells;
								while(cell != NULL) {
									printf("%s", cell->value);
									for(i = 0; i <= 
									(30 - strlen(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, "<=") == 0) {
							if(strcmp(string_cell->value, value) <= 0) {
								relation_found++;
								printf("\n");
								t_stringCell * cell = line->cells;
								while(cell != NULL) {
									printf("%s", cell->value);
									for(i = 0; i <= 
									(30 - strlen(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(strcmp(string_cell->value, value) == 0) {
								relation_found++;
								printf("\n");
								t_stringCell * cell = line->cells;
								while(cell != NULL) {
									printf("%s", cell->value);
									for(i = 0; i <= 
									(30 - strlen(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, "!=") == 0) {
							if(strcmp(string_cell->value, value) != 0) {
								relation_found++;
								printf("\n");
								t_stringCell * cell = line->cells;
								while(cell != NULL) {
									printf("%s", cell->value);
									for(i = 0; i <= (30 - strlen(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(strcmp(string_cell->value, value) >= 0) {
								relation_found++;
								printf("\n");
								t_stringCell * cell = line->cells;
								while(cell != NULL) {
									printf("%s", cell->value);
									for(i = 0; i <= 
									(30 - strlen(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						else if(strcmp(relation,">") == 0) {
							if(strcmp(string_cell->value, value) > 0) {
								relation_found++;
								printf("\n");
								t_stringCell * cell = line->cells;
								while(cell != NULL) {
									printf("%s", cell->value);
									for(i = 0; i <=
									(30 - strlen(cell->value)); i++) {
										printf(" ");
									}
									cell = cell->next;
								}
							}
						}
						line = line->next;
					}
				}
				if(relation_found != 0) {
				printf("\n");
				relation_found++;
			}
				printf("\n");
		}
		tables = tables->next;
	}
}
// Search if condidion it's true
int Search(t_table *tables,char *tb_name, char *cl_name, 
	char *relation, char* value) {
	int found_table = 0, found_column = 0, column_index = 0;
	while(tables != NULL) {
		column_index = 0; 
		// find the table needed
		if(strcmp(tb_name, tables->name) == 0) {
			found_table++;
			t_column *columns = tables->columns;
			while(columns != NULL) {
				column_index++;
				// find the column and its index
				if(strcmp(cl_name, columns->name) == 0) {
					found_column++;
					break;
				}
				columns = columns->next;
			}
			int index;
			if(found_column > 0) {
				if(tables->type == 0) {
					t_intLine *line = (t_intLine *)tables->lines;
					while(line != NULL) {
						index =  column_index;
						t_intCell *int_cell = line->cells;
						while(index != 1) {
							index--;
							int_cell = int_cell->next;
						}
						// find the relation operator and return 1 
						// if the comparing it's true 
						
						if(strcmp(relation, "<") == 0) {
							if(int_cell->value < atoi(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, "<=") == 0) {
							if(int_cell->value <= atoi(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(int_cell->value == atoi(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, "!=") == 0) {
							if(int_cell->value != atoi(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(int_cell->value >= atoi(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, ">") == 0) {
							if(int_cell->value > atoi(value)) {
								return 1;
							}
						}
						line = line->next;
					}
				}
					if(tables->type == 1) {
					t_floatLine *line = (t_floatLine *)tables->lines;
					while(line  != NULL) {
						index =  column_index;
						t_floatCell *float_cell = line->cells;
						while(index != 1) {
							index--;
							float_cell = float_cell->next;
						}
						if(strcmp(relation, "<") == 0) {
							if(float_cell->value < atof(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, "<=") == 0) {
							if(float_cell->value <= atof(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(float_cell->value == atof(value)) {
								return 1;
							}
						}
						else if(strcmp(relation,"!=") == 0) {
							if(float_cell->value != atof(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(float_cell->value >= atof(value)) {
								return 1;
							}
						}
						else if(strcmp(relation, ">") == 0) {
							if(float_cell->value > atof(value)) {
								return 1;
							}
						}
						line = line->next;
					}
				}
					if(tables->type == 2) {
					t_stringLine *line = (t_stringLine *)tables->lines;
					while(line != NULL) {
						index =  column_index;
						t_stringCell *string_cell = line->cells;
						while(index != 1) {
							index--;
							string_cell = string_cell->next;
						}
						if(strcmp(relation, "<") == 0) {
							if(strcmp(string_cell->value, value) < 0) {
								return 1;
							}
						}
						else if(strcmp(relation, "<=") == 0) {
							if(strcmp(string_cell->value, value) <= 0) {
								return 1;
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(strcmp(string_cell->value, value) == 0) {
								return 1;
							}
						}
						else if(strcmp(relation, "!=") == 0) {
							if(strcmp(string_cell->value, value) != 0) {
								return 1;
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(strcmp(string_cell->value, value) >= 0) {
								return 1;
							}
						}
						else if(strcmp(relation,">") == 0) {
							if(strcmp(string_cell->value, value) > 0) {
								return 1;
							}
						}
						line = line->next;
					}
				}
			}
		}
		tables = tables->next;
	}
	// Table not found case
	if(found_table == 0) {
		return -1;
	}
	// Column doesn't exists case
	if(found_column == 0) {
		return -2;
	}
	// Comparing return false
	return -3;
} 

void Delete_columns(t_column *columns) {
	t_column *current = columns, *next;
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	columns = NULL;
}

void Delete_Scell(t_stringCell *cell) {
	t_stringCell *current = cell, *next;
	while(current != NULL) {
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	cell = NULL;
}
void Delete_Fcell(t_floatCell *cell) {
	t_floatCell *current = cell, *next;
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	cell = NULL;
}
void Delete_Icell(t_intCell * cell) {
	t_intCell *current = cell, *next;
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	cell = NULL;
 }

 // Delete line of string cells
 void Delete_Sline(t_stringLine *line) {
 	t_stringLine *current = line, *next;
 	t_stringCell *cell;
 	while(current != NULL) {
 		next = current->next;
 		cell = current->cells;
 		Delete_Scell(cell);
 		free(current);
 		current = next;
 	}
 	line = NULL;
 }

 // Delete line of float cells
 void Delete_FLine(t_floatLine *line) {
 	t_floatLine *current = line, *next;
 	t_floatCell *cell;
 	while(current != NULL) {
 		next = current->next;
 		cell = current->cells;
 		Delete_Fcell(cell);
 		free(current);
 		current = next;
 	}
 	line = NULL;
 }

 // Delete line of integer cells
 void Delete_IntLine(t_intLine *line) {
 	t_intLine *current = line, *next;
 	t_intCell *cell;
 	while(current != NULL) {
 		next = current->next;
 		cell = current->cells;
 		Delete_Icell(cell);
 		free(current);
 		current = next;
 	}
 	line = NULL;
 }

void Delete_line(t_table *current, int type) {
	if(type == 0) {
		t_intLine *line = current->lines;
		Delete_IntLine(line);
	}
	if(type == 1) {
		t_floatLine *line = current->lines;
		Delete_FLine(line);
	}
	if(type == 2) {
		t_stringLine *line = current->lines;
		Delete_Sline(line);
	}
}

// Delete whole database 
// and free all alocated memory
void DELETE_DB(t_db **database) {
	t_db *data = *database;
	t_table *tables = data->tables;
	t_table *current = tables, *next;
	t_column *column;
	while(current != NULL) {
		next = current->next;
		column = current->columns;
		Delete_columns(column);
		Delete_line(current,current->type);
		free(current);
		current = next;
	}
	tables = NULL;
	free(tables);
	free(data);
}

// Delete a specific table
int DeleteTable(t_db **database, char *tb_name) {
	t_db *data = *database;
	t_table *tables = data->tables;
	t_table *current = tables, *prev;
	t_column *column;
	if(current != NULL && strcmp(current->name, tb_name) == 0) {
		data->tables = current->next;
		column = current->columns;
		Delete_columns(column);
		Delete_line(current,current->type);
		free(current);
		return 1;
	}
	while(current != NULL && strcmp(current->name,tb_name) != 0 ) {
		prev = current;
		current = current->next;
	}
	if(current == NULL) {
		return 0;
	}
	prev->next = current->next;
	column = current->columns;
	Delete_columns(column);
	Delete_line(current,current->type);
	free(current);
	return 1;
}

// Check for condition and the delete a cell if it's true
void delete_relation(t_table **table,char *tb_name, char *cl_name, 
	char *relation, char* value) {
	t_table *tables = *table;
	int  column_index;
	while(tables != NULL) {
		column_index = 0;
		if(strcmp(tb_name, tables->name) == 0) {
			t_column *columns = tables->columns;
			while(columns != NULL) {
				column_index++;
				if(strcmp(cl_name, columns->name) == 0) {
					break;
				}
				columns = columns->next;
			}
				int index, line_index = 0;
				if(tables->type == 0) {
					t_intLine *line = (t_intLine *)tables->lines, *prev;
					while(line != NULL) {
						index = column_index;
						line_index++;
						t_intCell *int_cell = line->cells;
						while(index != 1) {
							index--;
							int_cell = int_cell->next;
						}
						if(strcmp(relation, "<") == 0) {
							if(int_cell->value < atoi(value)) {
								// if index is one, head is removing and 
								// must change the head pointer
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Icell(line->cells);
									line = line->next;
									line_index--;
									continue;		
								}
								// delete the node which it's not head
								prev->next = line->next;
								Delete_Icell(line->cells);
								line = line->next;
								continue;
							}	
						}
						else if(strcmp(relation, "<=") == 0) {
							if(int_cell->value <= atoi(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Icell(line->cells);
									line = line->next;
									line_index--;
									continue;		
								}
								prev->next = line->next;
								Delete_Icell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(int_cell->value == atoi(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Icell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Icell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, "!=") == 0) {
							if(int_cell->value != atoi(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Icell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Icell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(int_cell->value >= atoi(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Icell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Icell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, ">") == 0) {
							if(int_cell->value > atoi(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Icell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Icell(line->cells);
								line = line->next;
								continue;
							}
						}
						prev = line;
						line = line->next;
					}
				}
					if(tables->type == 1) {
					t_floatLine *line = (t_floatLine *)tables->lines ,*prev;
					while(line != NULL) {
						index = column_index;
						line_index++;
						t_floatCell *float_cell = line->cells;
						while(index != 1) {
							index--;
							float_cell = float_cell->next;
						}
						if(strcmp(relation, "<") == 0) {
							if(float_cell->value < atof(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Fcell(line->cells);
									line = line->next;
									line_index--;
									continue;
								}
								prev->next = line->next;
								Delete_Fcell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, "<=") == 0) {
							if(float_cell->value <= atof(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Fcell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Fcell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(float_cell->value == atof(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Fcell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Fcell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation,"!=") == 0) {
							if(float_cell->value != atof(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Fcell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Fcell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(float_cell->value >= atof(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Fcell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Fcell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, ">") == 0) {
							if(float_cell->value > atof(value)) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Fcell(line->cells);
									line = line->next;
									line_index--;
									continue;	
								}
								prev->next = line->next;
								Delete_Fcell(line->cells);
								line = line->next;
								continue;	
							}
						}
						prev = line;
						line = line->next;
					}
				}
					if(tables->type == 2) {
					t_stringLine *line = (t_stringLine *)tables->lines,*prev;
					while(line != NULL) {
						index = column_index;
						line_index++;
						t_stringCell *string_cell = line->cells;
						while(index != 1) {
							index--;
							string_cell = string_cell->next;
						}
						if(strcmp(relation, "<") == 0) {
							if(strcmp(string_cell->value, value) < 0) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Scell(line->cells);
									line = line->next;
									line_index--;
									continue;
								}
								prev->next = line->next;
								Delete_Scell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, "<=") == 0) {
							if(strcmp(string_cell->value, value) <= 0) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Scell(line->cells);
									line = line->next;
									line_index--;
									continue;
								}
								prev->next = line->next;
								Delete_Scell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, "==") == 0) {
							if(strcmp(string_cell->value, value) == 0) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Scell(line->cells);
									line = line->next;
									line_index--;
									continue;
								}
								prev->next = line->next;
								Delete_Scell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, "!=") == 0) {
							if(strcmp(string_cell->value, value) != 0) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Scell(line->cells);
									line = line->next;
									line_index--;
									continue;
								}
								prev->next = line->next;
								Delete_Scell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation, ">=") == 0) {
							if(strcmp(string_cell->value, value) >= 0) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Scell(line->cells);
									line = line->next;
									line_index--;
									continue;
								}
								prev->next = line->next;
								Delete_Scell(line->cells);
								line = line->next;
								continue;
							}
						}
						else if(strcmp(relation,">") == 0) {
							if(strcmp(string_cell->value, value) > 0) {
								if(line_index == 1) {
									(*table)->lines = line->next;
									Delete_Scell(line->cells);
									line = line->next;
									line_index--;
									continue;
								}
								prev->next = line->next;
								Delete_Scell(line->cells);
								line = line->next;
								continue;
							}
						}
						prev = line;
						line = line->next;
					}
				}
		}
		tables = tables->next;
	}
}

int main() {
	char *command = malloc(MAX_CMD_LEN);
	char db_name[MAX_DB_NAME_LEN];
	char tb_name[MAX_TABLE_NAME_LEN];
	char line[200];
	char *line_sep[20];
	char *token;
	int table_size, res, found_table;
	t_db *database;
	t_table *tables;
	for(;;) {
		scanf("%s", command);
		if(strcmp(command, "INIT_DB") == 0) {
			scanf("%s", db_name);
			database = INIT_DB(db_name);
		}
		else if(strcmp(command, "CREATE") == 0) {
			fgets(line, 200, stdin);
			line[strcspn(line, "\n")] = '\0';
			table_size = 0;
			token = strtok(line, " ");
			while(token != NULL) {
				line_sep[table_size] = token;
				table_size++;
				token = strtok(NULL, " ");
			}
			if(exist_table(database->tables, line_sep) != 0) {
				printf("Table \"%s\" already exists.\n", line_sep[0]);
				continue;
			}
			database->tables = creat_table(&database->tables, line_sep);
			tables = database->tables;
			while(tables->next != NULL) {
				tables = tables->next;
			}
			tables->columns = create_column(table_size - 2, line_sep);
		}
		else if(strcmp(command, "PRINT_DB") == 0) {
			PRINT_DB(database);
		} 
		else if(strcmp(command, "PRINT") == 0) {
			scanf("%s",tb_name);
			print_table(database->tables,tb_name);
		}
		else if(strcmp(command, "SEARCH") == 0) {
			fgets(line, 200, stdin);
			line[strcspn(line, "\n")] = '\0';
			table_size = 0;
			token = strtok(line, " ");
			while(token != NULL) {
				line_sep[table_size] = token;
				table_size++;
				token = strtok(NULL, " ");
			}
			res = Search(database->tables, line_sep[0], line_sep[1],
			line_sep[2], line_sep[3]);
			if(res == -1) {
				printf("Table \"%s\" not found in database.\n", line_sep[0]);
			} 
			else if(res == -2) {
				printf("Table \"%s\" does not contain column \"%s\".\n",
				line_sep[0], line_sep[1]);
			}
			else if(res == -3) {
				print_columns(database->tables, line_sep[0]);
			}
			else if( res == 1) {
				print_lines(database->tables, line_sep[0], line_sep[1], 
				line_sep[2], line_sep[3]);
			}	
		}
		else if(strcmp(command, "ADD") == 0) {
			scanf("%s", tb_name);
			fgets(line, 200, stdin);
			line[strcspn(line, "\n")] = '\0';
			table_size = 0;
			token = strtok(line, " ");
			while(token != NULL) {
				line_sep[table_size] = token;
				table_size++;
				token = strtok(NULL, " ");
			}
			found_table = 0;
			tables = database->tables;
			while(tables != NULL) {
				if(strcmp(tb_name, tables->name) == 0) {
					found_table++;
					if(tables->type == 0) {
						tables->lines = create_intLine(&tables->lines,
						table_size, line_sep);
					}
					else if(tables->type == 1) {
						tables->lines = create_floatLine(&tables->lines, 
						table_size, line_sep);
					}
					else if(tables->type == 2) {
						tables->lines = create_stringLine(&tables->lines,
						table_size, line_sep);
						}
					}
				tables = tables->next;
			}
			if(found_table == 0) {
				printf("Table \"%s\" not found in database.\n", tb_name);
			}
		}
		else if(strcmp(command, "DELETE_DB") == 0) {
			free(command);
			DELETE_DB(&database);
			return 0;
		}
		else if(strcmp(command,"CLEAR") == 0) {
			scanf("%s",tb_name);
			tables = database->tables;
			while(tables != NULL) {
				if(strcmp(tables->name, tb_name) == 0) {
					Delete_line(tables,tables->type);
				}
				tables = tables->next;
			}
		}
		else if(strcmp(command,"DELETE") == 0) {
			fgets(line, 200, stdin);
			line[strcspn(line, "\n")] = '\0';
			table_size = 0;
			token = strtok(line, " ");
			while(token != NULL) {
				line_sep[table_size] = token;
				table_size++;
				token = strtok(NULL, " ");
			} 
			// delete table
			tables = database->tables;
			if(table_size == 1) {
				res = DeleteTable(&database,line_sep[0]);
				if(res == 0) {
					printf("Table \"%s\" not found in database.\n",
					line_sep[0]);
				}
			}
			// Check the relation and delete cell if it's true
			else {
				res = Search(database->tables, line_sep[0], line_sep[1], 
				line_sep[2], line_sep[3]);
				if(res == -1) {
					printf("Table \"%s\" not found in database.\n", 
					line_sep[0]);
				} 
				else if(res == -2) {
					printf("Table \"%s\" does not contain column \"%s\".\n", 
					line_sep[0], line_sep[1]);
				}
				else if(res == 1) {
					delete_relation(&tables, line_sep[0], line_sep[1], 
					line_sep[2], line_sep[3]); 
				}		
			}
		}
		else {
			printf("Unknown command: \"%s\".\n", command);
		}
	}
	return 0;
}