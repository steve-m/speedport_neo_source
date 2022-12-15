\NeedsTeXFormat{LaTeX2e}
\ProvidesPackage{fon} 
\RequirePackage{fancyhdr}
\RequirePackage{keyval}
\RequirePackage{ifthen}
\RequirePackage{color}
\RequirePackage{calc}
%
\newif\ifFON@verbose
\newif\ifFON@logos
\newif\ifFON@bookmarks          % have acrobat reader show bookmarks when opened
\newif\ifFON@sectionsleft       % boolean to put section's as labels on left
\newif\ifFON@sectionnumbers     % show section numbering
\newif\ifFON@oursections        % use our own default section defs
\newif\ifFON@showdate           % show the date under the document title
\newif\ifFON@showtitle          % show the title in the page header
\newif\ifFON@isproposal         % if this is a proposal, include hour/rate
                                % calculations
\newif\ifFON@showcopyright      % show copyright in the footer
\newif\ifFON@ismarketing        % if this is a marketing material
\newif\ifFON@isMarketing        % fancier marketing section
\newif\ifFON@sloppy             % make the right justification ragged
\newif\ifFON@hyperlinks         % whether or not to use hyperlinks
\newif\ifFON@letterhead         % whether or not to use the letterhead/footer
\newif\ifFON@printing           % whether the doc is for printing (on letterhead stock)
\newif\ifFON@pageno             % whether to use page numbers in footer
\newlength{\mylabelwidth}
\setlength{\mylabelwidth}{1.5in}
\newcommand{\HRule}{\rule{\linewidth}{0.5mm}}
\renewcommand{\headrulewidth}{.5pt}
\renewcommand{\footrulewidth}{0pt}
\renewcommand{\emph}[1]{\textbf{\textit{#1}}}
\def\labeltxtclr{white}
%
\ifx\undefined\fonpath\def\fonpath{gfx}\fi
\def\dot{$\bullet$}
\def\fon@header@logo{
    \ifx\undefined\FON@titlelogoscale\href{http://www.fon.com/}{\includegraphics[scale=.5]{\FON@titlelogo}}\else
    \href{http://www.fon.com/}{\includegraphics[scale=\FON@titlelogoscale]{\FON@titlelogo}}\fi}
\def\maintitle{\FON@title}
\def\fon@header@title{
  \ifx\undefined\FON@titleimage
  \ifFON@showtitle\ifdefined\FON@title{\sffamily\textbf{\FON@title}}\fi
  \ifFON@showdate\today\fi\else
    \ifx\undefined\FON@titleimagescale\includegraphics{\FON@titleimage}\else
    \includegraphics[scale=\FON@titleimagescale]{\FON@titleimage}\fi\fi}
\def\fon@footer@logo{\footnotesize\ \copyright\ 2010 \href{http://www.fon.com/}{FON Wireless} }
\def\fon@footer@page{\ifFON@pageno\ifthenelse{\equal{\pageref{LastPage}}{1}}{}{
  \small{Page \thepage\ of \pageref{LastPage}}}\fi}
\def\fon@footer@copyright{\scriptsize\ Copyright \copyright\ 2010 \href{http://www.fon.com/}{FON Wireless}}
\def\fonlogo{\begin{picture}(0,0)\put(-8,+8.5){\fon@header@logo}\end{picture}}
\def\fonlogoright{\begin{flushright}\setlength{\unitlength}{1pt}\begin{picture}(0,0)
  \put(-200,-15){\fon@header@logo}\end{picture}\end{flushright}}
\def\fon@colormargin{\begin{picture}(0,0)%
   \put(0,0){\rule[-\textheight-.5in]{\mylabelwidth-5pt}%
   {\textheight+.25in}}\end{picture}}
\def\fon@marginline{\hspace{-\FON@lmargin}\begin{picture}(0,0)%
   \put(0,0){% (below) moving forward mylabelwidth - .25in/4 + labelsep/2 - 3pt
   \hspace{\mylabelwidth}\hspace{\FON@lmargin}\hspace{-.0625in}\hspace{.5\labelsep}\hspace{-3pt}% ugly, I know
   \rule[-\textheight-.5in]{1pt}{\textheight+.25in}}\end{picture}}
\def\fon@colorstripe{\hspace{-\FON@lmargin}\begin{picture}(0,0)%
   \put(0,0){\rule[-1.5\paperheight]{\mylabelwidth+\FON@lmargin}%
   {2\paperheight}}\end{picture}}
\def\fon@setbool#1#2{\csname #2\ifx\relax#1\relax true\else#1\fi\endcsname}
\def\fon@checkbool#1{\csname ifFON@#1\endcsname #1\space\else\fi}
\def\fon@warning#1{\ifFON@verbose\PackageWarningNoLine{fonetworks}{#1}\fi}
\def\fon@help#1{UNKNOWN\marginpar{\textcolor{red}{$\Leftarrow$}{\footnotesize #1}}}
\ifFON@verbose\PackageWarningNoLine{fonetworks}{#1}\fi
\def\ifdefined#1#2{\ifx\undefined#1\else #2\fi}
\def\ifdefinedhelp#1#2#3{\ifx\undefined#1 \fon@help{#3}\else #2\fi}
\def\hashadd#1#2#3{%
  \expandafter\def\csname#1 #2\endcsname{#3}%
  \expandafter\ifx\csname keys #1\endcsname\relax
    \expandafter\def\csname keys #1\endcsname{}\fi
  \toks0\expandafter\expandafter\expandafter{\csname keys #1\endcsname\do{#2}}%
  \expandafter\edef\csname keys #1\endcsname{\the\toks0}}
\def\hashlookup#1#2{\csname#1 #2\endcsname}
\def\hashdoall#1{\csname keys #1\endcsname}
% quotes are only used in Marketing style
\def\addquote#1#2#3{\hashadd{quote}{#1}{#2}\hashadd{quoteby}{#1}{#3}\hashadd{q}{#1}{x}}
\def\addquotespec#1#2{\hashadd{quote}{#1}{#2}\hashadd{quoteby}{#1}{x}\hashadd{q}{#1}{x}}
\def\fon@showquote{%
  \ifthenelse{\equal{\hashlookup{q}{\thepage}}{x}}{%
    \newbox\@mltitle\begin{picture}(0,0)%
    \put(0,0){\sbox{\@mltitle}{\raisebox{-\FON@headsep-16pt}{%
	  \textcolor{\labeltxtclr}{\footnotesize\textbf{%
              \parbox[t]{\mylabelwidth+\FON@lmargin}{\centering%
		\ifthenelse{\equal{\hashlookup{quoteby}{\thepage}}{x}}{}{``}
		\parbox[t]{\mylabelwidth-10pt}{\raggedright
		  \hashlookup{quote}{\thepage}
		  \ifthenelse{\equal{\hashlookup{quoteby}{\thepage}}{x}}{}{''\newline\newline
		    -- \hashlookup{quoteby}{\thepage}}}}}}}}%
      \dp\@mltitle=0pt\usebox\@mltitle}\end{picture}}{}}
%
% 
\def\fon@init{
  \FON@verbosefalse 
  \FON@logostrue
  \FON@sectionsleftfalse
  \FON@sectionnumbersfalse
  \FON@oursectionstrue
  \FON@showdatefalse
  \FON@showtitletrue
  \FON@showcopyrightfalse
  \FON@isproposalfalse
  \FON@ismarketingfalse
  \FON@isMarketingfalse
  \FON@sloppytrue
  \FON@hyperlinkstrue
  \FON@letterheadtrue
  \FON@printingfalse
  \FON@pagenotrue
  \def\FON@fontsize{12}
  \def\FON@top{0pt}
  \def\FON@head{1in}
  \def\FON@headsep{5pt}
  \def\FON@bottom{.5in}
  \def\FON@lmargin{.5in}
  \def\FON@rmargin{.5in}
  \def\FON@author{FON Wireless}
  \def\FON@titlelogo{fon.png}
  \let\FON@style\undefined
  \let\FON@title\undefined
  \let\FON@titleimage\undefined
  \let\FON@titleimagescale\undefined
  \let\FON@titlelogoscale\undefined
  \let\FON@subject\undefined
  \let\FON@keywords\undefined
  \let\FON@client\undefined
  \let\FON@clientaddr\undefined
  \let\FON@contact\undefined
  \let\FON@signer\undefined
}
%
% option definitions
\define@key{FON}{verbose}[true]{\lowercase{\fon@setbool{#1}}{FON@verbose}}
\define@key{FON}{nologos}[false]{\lowercase{\fon@setbool{#1}}{FON@logos}}
\define@key{FON}{bookmarks}[true]{\FON@bookmarkstrue}
\define@key{FON}{copyright}[true]{\FON@showcopyrighttrue}
\define@key{FON}{sloppy}{\ifx #1\FON@sloppytrue\else\FON@sloppyfalse\fi}
\define@key{FON}{hyperlinks}{\ifx #1\FON@hyperlinkstrue\else\FON@hyperlinksfalse\fi}
\define@key{FON}{letterhead}{\ifx #1\FON@letterheadtrue\else\FON@letterheadfalse\fi}
\define@key{FON}{printing}[true]{\FON@printingtrue}
\define@key{FON}{nopageno}[true]{\FON@pagenofalse}
\define@key{FON}{top}{\edef\FON@top{#1}}
\define@key{FON}{head}{\edef\FON@head{#1}}
\define@key{FON}{headsep}{\edef\FON@headsep{#1}}
\define@key{FON}{bottom}{\edef\FON@bottom{#1}}
\define@key{FON}{lmargin}{\edef\FON@lmargin{#1}}
\define@key{FON}{rmargin}{\edef\FON@rmargin{#1}}
\define@key{FON}{fontsize}{\edef\FON@fontsize{#1}}
\define@key{FON}{style}{\edef\FON@style{#1}}
\define@key{FON}{title}{\edef\FON@title{#1}}
\define@key{FON}{titleimage}{\edef\FON@titleimage{#1}}
\define@key{FON}{titleimagescale}{\edef\FON@titleimagescale{#1}}
\define@key{FON}{titlelogo}{\edef\FON@titlelogo{#1}}
\define@key{FON}{titlelogoscale}{\edef\FON@titlelogoscale{#1}}
\define@key{FON}{subject}{\edef\FON@subject{#1}}
\define@key{FON}{keywords}{\edef\FON@keywords{#1}}
\define@key{FON}{author}{\edef\FON@author{#1}}
\define@key{FON}{client}{\edef\FON@client{#1}}
\define@key{FON}{clientaddr}{\edef\FON@clientaddr{#1}}
\define@key{FON}{contact}{\edef\FON@contact{#1}}
\define@key{FON}{signer}{\edef\FON@signer{#1}}
%
% option processor
\def\fon@process{
  \ifnum\FON@fontsize=10\PassOptionsToClass{10pt}{article}\else
        \ifnum\FON@fontsize=11\PassOptionsToClass{11pt}{article}\else
        \ifnum\FON@fontsize=12\PassOptionsToClass{12pt}{article}\else
        \fon@warning{Invalid Option fontsize=\FON@fontsize}\fi\fi\fi
  \ifthenelse{\boolean{FON@bookmarks}}{
        \PassOptionsToPackage{bookmarks=true,bookmarksopen=true}{hyperref}}{
        \PassOptionsToPackage{bookmarks=false,bookmarksopen=false}{hyperref}}
  \ifdefined\FON@title{
        \PassOptionsToPackage{pdftitle={\FON@title}}{hyperref}}
  \ifdefined\FON@subject{
        \PassOptionsToPackage{pdfsubject={\FON@subject}}{hyperref}}
  \ifdefined\FON@author{
        \PassOptionsToPackage{pdfauthor={\FON@author}}{hyperref}}
  \ifdefined\FON@keywords{
        \PassOptionsToPackage{pdfkeywords={\FON@keywords}}{hyperref}}
  \ifdefined\FON@style{
        \ifthenelse{\equal{\FON@style}{doc}}
        {\FON@showdatefalse\FON@sectionnumberstrue}
        {\ifthenelse{\equal{\FON@style}{letter}}
        {\FON@showdatefalse\FON@sectionnumberstrue
         \renewcommand{\headrulewidth}{0pt}}
        {\ifthenelse{\equal{\FON@style}{agreement}}
        {\FON@showdatefalse\FON@sectionnumberstrue}
        {\ifthenelse{\equal{\FON@style}{proposal}}
          {\FON@showdatefalse\FON@sectionnumberstrue
           \FON@isproposaltrue}
            {\ifthenelse{\equal{\FON@style}{Marketing}}
              {\FON@showdatefalse\FON@showtitlefalse\FON@isMarketingtrue
                \edef\FON@lmargin{.3in}\edef\FON@rmargin{.3in}\edef\FON@bottom{.7in}
                \setlength{\mylabelwidth}{2.5in-\FON@lmargin}
                \renewcommand{\headrulewidth}{0pt}}
            {\ifthenelse{\equal{\FON@style}{marketing}}
              {\FON@showdatefalse\FON@showtitlefalse\FON@ismarketingtrue\FON@sectionslefttrue
                \setlength{\mylabelwidth}{2in}
                \renewcommand{\headrulewidth}{0pt}}
              {\fon@warning{Invalid Option style=\FON@style}}}}}}}}
}
%
% run options
\def\fon@setkey{\setkeys{FON}}
\let\fon@origExecuteOptions\ExecuteOptions
\let\ExecuteOptions\fon@setkey
\fon@init
\InputIfFileExists{fonetworks.cfg}
           {\typeout{****************************************^^J%
                     * Local config file fonetworks.cfg used^^J%
                     ****************************************}}{}
\let\ExecuteOptions\fon@origExecuteOptions
\def\ProcessOptionsWithKV#1{
  \let\@tempa\@empty
  \@for\CurrentOption:=\@classoptionslist\do{
    \@ifundefined{KV@#1@\CurrentOption}
    {}{\edef\@tempa{\@tempa,\CurrentOption,}}}
  \edef\@tempa{\noexpand\setkeys{#1}{\@tempa\@ptionlist{\@currname.\@currext}}}
  \@tempa\AtEndOfPackage{\let\@unprocessedoptions\relax}}
\ProcessOptionsWithKV{FON}
\fon@process
%
% Pre-package option processing
\ifFON@printing\def\labeltxtclr{black}\FON@letterheadfalse\FON@hyperlinksfalse\fi
\ifFON@hyperlinks\def\fonlink#1#2{\hyperlink{#1}{#2}}\def\fonhref#1#2{\href{#1}{#2}}
\else\def\fonlink#1#2{#2}\def\fonhref#1#2{#2}\fi
%
% load in classes and packages
\LoadClass[pdftex]{article}
\PassOptionsToPackage{pdftex}{hyperref}
\PassOptionsToPackage{top=\FON@top}{geometry}
\PassOptionsToPackage{head=\FON@head}{geometry}
\PassOptionsToPackage{headsep=\FON@headsep}{geometry}
\PassOptionsToPackage{bottom=\FON@bottom}{geometry}
\PassOptionsToPackage{lmargin=\FON@lmargin}{geometry}
\PassOptionsToPackage{rmargin=\FON@rmargin}{geometry}
\PassOptionsToPackage{titles}{tocloft}
\RequirePackage{tocloft}
\RequirePackage{geometry}
\RequirePackage{color}
\RequirePackage{nopageno}
\RequirePackage{graphicx}
\RequirePackage{lastpage}
\RequirePackage{colortbl}
\RequirePackage{verbatim}
\RequirePackage{longtable}
\RequirePackage{alltt}
\RequirePackage{nameref}
\RequirePackage[colorlinks,
  linkcolor={blue},
  citecolor={blue},
  urlcolor={blue}]{hyperref}
\RequirePackage{wrapfig}
\RequirePackage{enumerate}
\RequirePackage{fp}
\RequirePackage{ulem}
\RequirePackage[titles]{tocloft}
%
% some globals
\setlength{\intextsep}{2pt}% in wrapfig
\setlength{\topskip}{0.2in}
\setlength{\parindent}{0pt}
\setlength{\parskip}{10pt}
\renewcommand{\cfttoctitlefont}{\sffamily}
\setlength{\cftbeforesecskip}{0.5ex}
\ifFON@sectionnumbers\setcounter{secnumdepth}{4}
\else\setcounter{secnumdepth}{4}\fi
\setlength{\minrowclearance}{2pt}
\def\Cplusplus{C\raise.5ex\hbox{\tiny ++}}
\renewcommand{\labelitemi}{$\circ$}
\renewcommand{\labelitemii}{$\rightarrow$}
%
% Post-package option processing
\ifFON@isMarketing\renewcommand{\emph}[1]{\textbf{#1}}\fi
\ifFON@ismarketing\renewcommand{\emph}[1]{\textbf{#1}}\fi

\def\signaturepage#1{
  \phantomsection\addcontentsline{toc}{section}{Signature Page} #1\\[15pt]\begin{tabular}{@{}ll}
  \parbox[t]{.5\textwidth}{\ifx\undefined\FON@client Company:\else\FON@client\fi\\ By:
  \ifx\undefined\FON@contact\else\FON@contact\fi\\[15pt]\rule{3in}{1pt}\\[5pt]
  Date:\\[10pt]\rule{1in}{1pt}} & \parbox[t]{.5\textwidth}{Flying Fish
  Software, LLC.\\By:
  \ifx\undefined\FON@signer\else\FON@signer\fi\\[15pt]\rule{3in}{1pt}\\[5pt]
  Date:\\[10pt]\rule{1in}{1pt}}\end{tabular}\\}
%
%  Our own section, subsection and subsubsection commands, if desired.
\ifFON@oursections
  \renewcommand\section{\@startsection{section}{1}{0pt}
     {-1ex \@plus -.25ex \@minus -.1ex}{.75ex \@plus .1ex}
     {\normalsize\bfseries}}
  \renewcommand\subsection{\@startsection{subsection}{2}{0pt}
     {-.5ex\@plus -.25ex \@minus -.1ex}{.5ex \@plus .1ex}
     {\normalsize\bfseries}}
  \renewcommand\subsubsection{\@startsection{subsubsection}{3}{0pt}
     {-.5ex\@plus -.25ex \@minus -.1ex}{.5ex \@plus .1ex}
     {\normalsize\bfseries}}
  \newcommand\subsubsubsection{\@startsection{paragraph}{4}{0pt}
     {-.5ex\@plus -.25ex \@minus -.1ex}{.5ex \@plus .1ex}
     {\normalsize\bfseries}}
\fi
%
%  Add a `hidden' entry to the TOC
\def\addtoc#1#2{\phantomsection\addcontentsline{toc}{#1}{#2}}
%
%  Basic coverpage environment. 
\newenvironment{coverpagememo}{\addtoc{section}{Cover Letter}
   \begin{titlepage}}{\end{titlepage}}
%
%  The ``specs'' environment provices a basic nested list of project
%  specifications.
\newenvironment{specs}[1]{\begin{list}{#1}{%
   \setlength\topsep{0pt plus 4pt minus 2pt}%
   \setlength\parsep{2pt plus 4pt minus 2pt}%
   \setlength\itemsep{2pt plus 4pt minus 1pt}%
   \setlength\rightmargin{5ex}%
   \setlength\leftmargin{5ex}%
   \setlength\labelwidth{5ex}}}{\end{list}}
\newcounter{fon@i@depth}
\renewenvironment{itemize}
  {\setcounter{fon@i@depth}{\value{fon@i@depth} + 1}
   \begin{specs}{\csname labelitem\roman{fon@i@depth}\endcsname}}
  {\end{specs}\setcounter{fon@i@depth}{\value{fon@i@depth} - 1}}
\newenvironment{definitions}{\begin{list}{}{
   \setlength{\labelsep}{0pt}
   \setlength{\leftmargin}{0pt}
   \setlength{\labelwidth}{0pt}
   \renewcommand{\makelabel}[1]{\uline{##1}:~~}}}{\end{list}}
%
%  The ``llist'' environment provides a basic left column 'label' and a
%  right column text block. The basic format of certain proposals or
%  reports. 
\newbox\@ltitle
\newenvironment{llist}{\begin{list}{}{
   \setlength\labelwidth{\mylabelwidth}
   \setlength\leftmargin{\labelwidth}
   \addtolength\leftmargin{\labelsep}
   \itemsep 6pt plus 2pt minus 2pt
   \parsep 10pt plus 2pt minus 2pt
   \def\section##1{\addtocounter{section}{1}\setcounter{subsection}{0}\setcounter{subsubsection}{0}     
      \phantomsection\addcontentsline{toc}{subsection}{##1}
      \setbox\@ltitle=\hbox{\textbf{\ifFON@ismarketing%
          \hspace{5pt}\parbox[t]{\mylabelwidth-.25in}{
          \ifFON@printing\raggedleft\else\raggedright\fi\textcolor{\labeltxtclr}{##1}}%
          \else##1\fi}}
      \dp\@ltitle=0pt\item[\copy\@ltitle]
      \ifdim\wd\@ltitle>\labelwidth\leavevmode \\* \else \fi}
   \def\makelabel##1{##1\hfill}}}{\end{list}}
\newenvironment{mllist}{\begin{list}{}{
   \setlength\labelsep{10pt}
   \setlength\labelwidth{\mylabelwidth}
   \setlength\leftmargin{\labelwidth}
   \addtolength\leftmargin{\labelsep}
   \itemsep 6pt plus 2pt minus 2pt
   \parsep 10pt plus 2pt minus 2pt}}{\end{list}}
%
%  When in the llist environments, the ``resetmargin'' environment will
%  reset the margins to the original page. This allows for the placement of
%  charts and graphs. 
\newenvironment{resetmargin}{\begin{list}{}{
  \setlength{\leftmargin}{-\mylabelwidth}\addtolength{\leftmargin}{-\labelsep}
  \setlength{\listparindent}{\parindent}\setlength{\itemindent}{\parindent}
  \setlength{\parsep}{\parskip}\setlength{\topsep}{0pt}\setlength{\partopsep}{0pt}
  \setlength{\parskip}{0pt}\setlength{\itemsep}{0pt}}\item[]}{\end{list}}
%
%  The environemt ``fullpage'' will return to the paperwidth margins. This
%  is used in the placement of the footer image.
\newenvironment{fullpage}{\begin{list}{}{\setlength{\labelsep}{0pt}
  \setlength{\leftmargin}{\paperwidth - \textwidth}
  \setlength{\leftmargin}{\leftmargin / 2}
  \setlength{\leftmargin}{-\leftmargin}}\item[]}{\end{list}}
%
% Configure the page.
\pagestyle{fancy}
\fancyhf{} % Clear all header and footer fields
\def\hfreset{
  \fancyhead[RE,LO]{
  \ifFON@logos
    \ifFON@letterhead
       \ifFON@isMarketing\fonlogoright\fon@colorstripe\fon@showquote
       \else\ifFON@ismarketing\fonlogo\fon@colormargin
            \else\fon@header@logo\fi
       \fi
    \else
      \ifFON@printing\fon@marginline
         \ifFON@isMarketing\fon@showquote\fi
      \else
         \ifFON@isMarketing\fon@colormargin\fon@showquote
         \else\ifFON@ismarketing\fon@colormargin\fi
         \fi
      \fi
    \fi
  \fi}
  \fancyhead[RE,LO]{\fon@header@logo}
  \fancyhead[LE,RO]{\fon@header@title}
  \fancyfoot[RE,LO]{\ifFON@logos\ifFON@letterhead\fon@footer@logo\fi\fi}
  \fancyfoot[LE,RO]{\fon@footer@page}
  \ifFON@showcopyright\fancyfoot[RE,LO]{\fon@footer@copyright}\fi}
\hfreset
\ifFON@sloppy\raggedright\fi
\AtBeginDocument{
  \begin{sffamily}
  \ifFON@isMarketing\begin{mllist}\item\fi
  \ifFON@sectionsleft\begin{llist}\fi
}
\AtEndDocument{
  \ifFON@isMarketing\end{mllist}\fi
  \ifFON@sectionsleft\end{llist}\fi
  \end{sffamily}
}
