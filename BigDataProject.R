library(rvest)

kozbesz = NULL
fej= NULL
test = NULL
penz = NULL
szam = NULL

N = 13
r = 20000

url <-read_html("http://www.kozbeszerzes.hu/adatbazis/mutat/hirdetmeny/portal_1234_2017/")
for (i in 1:N){
fej <- c(fej, url %>% 
  html_nodes(xpath = paste("/html/body/div[7]/div/div[1]/table/tr[",toString(i),"]/th/text()", sep="")) %>%
  html_text())
}

kozbesz <- data.frame(matrix(ncol = N, nrow = 0))
colnames(kozbesz) <- fej

for (y in 1:5){
for (j in 1:r){
  test = NULL
  url <-read_html(paste("http://www.kozbeszerzes.hu/adatbazis/mutat/hirdetmeny/portal_",toString(1000+j),"_",toString(2012+y),"/",sep=""))
  for (k in 1:N){
    x = url %>% 
      html_nodes(xpath = paste("/html/body/div[7]/div/div[1]/table/tr[",toString(k),"]/td/text()", sep="")) %>%
      html_text()
    test <- c(test, x)
    if(identical(x, character(0))){
      test <- c(test, NaN)
    }
  }
  
  kozbesz[j+r*(y-1),] <- test
  
  content = url %>% 
    html_nodes(xpath = "/html/body/div[7]/div/div[2]/div/div[2]") %>%
    html_text()
  
  content2 = url %>% 
    html_nodes(xpath = "/html/body/div[7]/div/div[2]/div/div[4]") %>%
    html_text()
  
  if(identical(content, character(0))){
    penz <- c(penz, NaN)
    szam <- c(szam, NaN)
  }
  else{
    
  splitted = unlist(strsplit(as.character(content), split = " ", fixed = TRUE))
  splitted2 = unlist(strsplit(as.character(content2), split = " ", fixed = TRUE))
  if(identical(grep("Érték:", splitted), integer(0))){
    penz <- c(penz, NaN)
  }
  else{
    ertek <- splitted[[grep("Érték:", splitted)[1]+2]]
    penz <- c(penz, ertek)
  }
  if(identical(grep("beérkezett", splitted2), integer(0))){
    szam <- c(szam, NaN)
  }
  else{
    ertek2 <- splitted2[[grep("beérkezett", splitted2)[1]+4]]
    szam <- c(szam, ertek2)
  }
  }
}
}
kozbesz['Érték'] <- penz
kozbesz['ajanlatok'] <- szam

write.csv(kozbesz, file = "kozbesz.csv")

names(kozbesz)[names(kozbesz) == "Nyertes ajánlattevő:"] <- "nyertes"
names(kozbesz)[names(kozbesz) == "Teljesítés helye:"] <- "hely"
names(kozbesz)[names(kozbesz) == "Közzététel dátuma:"] <- "datum"
names(kozbesz)[names(kozbesz) == "Eljárás fajtája:"] <- "fajta"
names(kozbesz)[names(kozbesz) == "Hirdetmény típusa:"] <- "tipus"
names(kozbesz)[names(kozbesz) == "Beszerzés tárgya:"] <- "targy"

colnames(kozbesz)[12] <- "ajanlattipus"
colnames(kozbesz)[13] <- "tevkor"

kozbesz$Érték <- as.numeric(kozbesz$Érték)

kozbesz$ajanlatok <- as.numeric(kozbesz$ajanlatok)

kozbesz <- na.omit(kozbesz)

kozbesz <- kozbesz[which(kozbesz$Érték > 1000),]

mean(kozbesz$Érték)

hist(kozbesz$Érték[kozbesz$Érték < 100000000])

kozbesz$logertek <- log(kozbesz$Érték)

barplot(table(kozbesz$targy))
barplot(table(kozbesz$tipus))

unique(kozbesz$targy)[table(kozbesz$targy) == 1]

reg <- lm(logertek~targy+tipus+fajta+ajanlatok+ajanlattipus+tevkor, data=kozbesz)

summary(reg)

plot(kozbesz$logertek,reg$residuals)

library(leaps)

regfit.full=regsubsets(logertek~targy+tipus+fajta+ajanlatok+ajanlattipus+tevkor, data=kozbesz,nvmax=3, really.big = T)
