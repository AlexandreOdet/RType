#!/bin/sh
## enemy.sh for enemy in /home/lopez_t/rtype/enemies
## 
## Made by Thibaut Lopez
## Login   <lopez_t@epitech.net>
## 
## Started on  Thu Dec 17 13:35:40 2015 Thibaut Lopez
## Last update Tue Dec 22 16:32:02 2015 Thibaut Lopez
##

if [ -z "$1" ]
then
    printf "Usage: enemy.sh enemy_name\n"
    exit
fi

name=`getent passwd $LOGNAME | cut -d: -f5 | cut -d, -f1`
date=`LC_ALL=en_EN.utf8 date "+%a %b %d %H:%M:%S %Y"`

touch "${1}.hh"
touch "${1}.cpp"

## Header du .hh
echo "//" >> "${1}.hh"
echo "// ${1}.hh for ${1} in `pwd`" >> "${1}.hh"
echo "//" >> "${1}.hh"
echo "// Made by $name" >> "${1}.hh"
echo "// Login   <${USER}@epitech.net>" >> "${1}.hh"
echo "//" >> "${1}.hh"
echo "// Started on  ${date} $name" >> "${1}.hh"
echo "// Last update ${date} $name" >> "${1}.hh"
echo "//" >> "${1}.hh"
echo "" >> "${1}.hh"

## Contenu du .hh
echo "#ifndef	`echo "${1}_HH" | tr '[:lower:]' '[:upper:]'`" >> "${1}.hh"
echo "#define	`echo "${1}_HH" | tr '[:lower:]' '[:upper:]'`" >> "${1}.hh"
echo "" >> "${1}.hh"
echo "#include \"ILoader.hh\"" >> "${1}.hh"
echo "#include \"NormalShoot.hh\"" >> "${1}.hh"
echo "#include \"MediumShoot.hh\"" >> "${1}.hh"
echo "#include \"LongShoot.hh\"" >> "${1}.hh"
echo "#include \"EnemyShoot.hh\"" >> "${1}.hh"
echo "#include \"STTime.hh\"" >> "${1}.hh"
echo "#include \"Client.hh\"" >> "${1}.hh"
echo "#include \"Game.hpp\"" >> "${1}.hh"
echo "" >> "${1}.hh"
echo "class	${1} : public IEnemy" >> "${1}.hh"
echo "{" >> "${1}.hh"
echo "public:" >> "${1}.hh"
echo "  ${1}();" >> "${1}.hh"
echo "  virtual ~${1}();" >> "${1}.hh"
echo "  void		behave(const Creature *, const Game *, eAction &, uAction &);" >> "${1}.hh"
echo "  eCreature	getType() const;" >> "${1}.hh"
echo "  std::size_t	getMaxHealth() const;" >> "${1}.hh"
echo "  std::size_t	getHeight() const;" >> "${1}.hh"
echo "  std::size_t	getWidth() const;" >> "${1}.hh"
echo "};" >> "${1}.hh"
echo "" >> "${1}.hh"
echo "extern \"C\" IEnemy	*loadLib();" >> "${1}.hh"
echo "" >> "${1}.hh"
echo "#endif" >> "${1}.hh"

## Header du .cpp
echo "//" >> "${1}.cpp"
echo "// ${1}.cpp for ${1} in `pwd`" >> "${1}.cpp"
echo "//" >> "${1}.cpp"
echo "// Made by $name" >> "${1}.cpp"
echo "// Login   <${USER}@epitech.net>" >> "${1}.cpp"
echo "//" >> "${1}.cpp"
echo "// Started on  ${date} $name" >> "${1}.cpp"
echo "// Last update ${date} $name" >> "${1}.cpp"
echo "//" >> "${1}.cpp"
echo "" >> "${1}.cpp"

## Contenu du .cpp
echo "#include \"${1}.hh\"" >> "${1}.cpp"
echo "" >> "${1}.cpp"
echo "${1}::${1}()" >> "${1}.cpp"
echo "{" >> "${1}.cpp"
echo "}" >> "${1}.cpp"
echo "" >> "${1}.cpp"
echo "${1}::~${1}()" >> "${1}.cpp"
echo "{" >> "${1}.cpp"
echo "}" >> "${1}.cpp"
echo "" >> "${1}.cpp"
echo "void		${1}::behave(const Creature *me, const Game *game, eAction &action, uAction &arg)" >> "${1}.cpp"
echo "{" >> "${1}.cpp"
echo "  (void)me;" >> "${1}.cpp"
echo "  (void)game;" >> "${1}.cpp"
echo "  (void)action;" >> "${1}.cpp"
echo "  (void)arg;" >> "${1}.cpp"
echo "}" >> "${1}.cpp"
echo "" >> "${1}.cpp"
echo "eCreature		${1}::getType() const" >> "${1}.cpp"
echo "{" >> "${1}.cpp"
echo "  return (ZIPP);" >> "${1}.cpp"
echo "}" >> "${1}.cpp"
echo "" >> "${1}.cpp"
echo "std::size_t	${1}::getMaxHealth() const" >> "${1}.cpp"
echo "{" >> "${1}.cpp"
echo "  return (1);" >> "${1}.cpp"
echo "}" >> "${1}.cpp"
echo "" >> "${1}.cpp"
echo "std::size_t	${1}::getHeight() const" >> "${1}.cpp"
echo "{" >> "${1}.cpp"
echo "  return (1);" >> "${1}.cpp"
echo "}" >> "${1}.cpp"
echo "" >> "${1}.cpp"
echo "std::size_t	${1}::getWidth() const" >> "${1}.cpp"
echo "{" >> "${1}.cpp"
echo "  return (1);" >> "${1}.cpp"
echo "}" >> "${1}.cpp"
echo "" >> "${1}.cpp"
echo "extern \"C\" IEnemy	*loadLib()" >> "${1}.cpp"
echo "{" >> "${1}.cpp"
echo "  return (new ${1}());" >> "${1}.cpp"
echo "}" >> "${1}.cpp"

emacs -nw "${1}.cpp" "${1}.hh"
