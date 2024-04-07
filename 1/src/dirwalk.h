#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <getopt.h>
#include <unistd.h>

int compare(const struct dirent **a, const struct dirent **b);

void listAll(const char* path);

void listFiles(const char *path);

void listDirectory(const char* path);

void listSort(const char* path);

void listLink(const char *path);