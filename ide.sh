includeFiles=$(find ./include -name "*.h")
srcFiles=$(find ./src -name "*.cpp")
testFiles=$(find ./test -name "*.h" -name "*.cpp")

filter(){
    filteredFiles=()
    for f in $1
    do
	if "namespace $2" in $(cat f)
	then
	    filteredFiles+=(f)
	fi
    done
}

if test $# -eq 0
then
    emacs $includeFiles
else 
    case $1 in
	include)
	    emacs $includeFiles
	    ;;
	tests)
	    emacs $testFiles
	    ;;
	src)
	    emacs $srcFiles
	    ;;
	nsCore)
	    filter($includeFiles, "Core")
	    ;;
	nsAI)
	    ;;
	nsAlgorithm)
	    ;;
	nsUtilities)
	    ;;
	nsRL)
	    ;;
	nsSupervisedLearning)
	    ;;
	nsDP)
	    ;;
	nsLP)
	    ;;
	nsG)
	    ;;
	nsPolicy)
	    ;;
	nsHash)
	    ;;
    esac
fi
