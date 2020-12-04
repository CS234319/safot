"%s/\\begin{itemize}/\\החל{ציינון}/ge
"%s/\\end{itemize}/\\סוף{ציינון}/ge
"%s/\\begin{enumerate}/\\החל{ספרור}/ge
"%s/\\end{enumerate}/\\סוף{ספרור}/ge
"%s/\\begin{description}/\\החל{תיאור}/ge
"%s/\\end{description}/\\סוף{תיאור}/ge


"%s/\\begin{definition}/\\החל{הגדרה}/ge
"%s/\\end{definition}/\\סוף{הגדרה}/ge
"%s/\\begin{example}/\\החל{דוגמה}/ge
"%s/\\end{example}/\\סוף{דוגמה}/ge


%s/\\החל{ציינון}/\\begin{itemize}/ge
%s/\\סוף{ציינון}/\\end{itemize}/ge
%s/\\החל{ספרור}/\\begin{enumerate}/ge
%s/\\סוף{ספרור}/\\end{enumerate}/ge
%s/\\החל{תיאור}/\\begin{description}/ge
%s/\\סוף{תיאור}/\\end{description}/ge

%s/\\כיתוב{\(.*\)}/\\כיתוב|\1|/ge 
%s/\\תגית{\(.*\)}/\\תגית|\1|/ge 

%s/\\item/✦/ge
%s/מיני ליספ/מיני-ליספ/ge
""%s/ביטוי-S/ביטוי-\E|S|/ge
""%s/ביטויי-S/ביטויי-\E|S|/ge
""%s/ביטוי\~S/ביטוי\~\\E|S|/ge
""%s/ביטויי\~S/ביטויי\~\\E|S|/ge
""%s/ביטוי S/ביטוי\~\\E|S|/ge
""%s/ביטויי S/ביטויי\~\\E|S|/ge
""%s/ביטוי \\E|S|/ביטוי\~\\E|S|/ge
""%s/ביטויי \\E|S|/ביטויי\~\\E|S|/ge
%s/היתה/הייתה/ge

%s/$⟨$/⟨/ge
%s/$⟩$/⟩/ge
%s/\([א-ת]\)\$/\1~$/ge
%s/\<מ \+/מ-/ge
%s/\<ש \+/ש-/ge
%s/\<ה \+/ה-/ge
%s/\<ו \+/ו-/ge
%s/\<כ \+/כ-/ge
%s/\<ל \+/ל-/ge
%s/\<ב \+/ב-/ge

source ~/bin/+short
set nospell

