library(rvest)

kozbesz = NULL
fej= NULL
test = NULL
penz = NULL

N = 13

url <-read_html("http://www.kozbeszerzes.hu/adatbazis/mutat/hirdetmeny/portal_1234_2017/")
for (i in 1:N){
fej <- c(fej, url %>% 
  html_nodes(xpath = paste("/html/body/div[7]/div/div[1]/table/tr[",toString(i),"]/th/text()", sep="")) %>%
  html_text())
}

kozbesz <- data.frame(matrix(ncol = N, nrow = 0))
colnames(kozbesz) <- fej


for (j in 1:10){
  test = NULL
  url <-read_html(paste("http://www.kozbeszerzes.hu/adatbazis/mutat/hirdetmeny/portal_",toString(1233+j),"_2017/",sep=""))
  for (k in 1:N){
    x = url %>% 
      html_nodes(xpath = paste("/html/body/div[7]/div/div[1]/table/tr[",toString(k),"]/td/text()", sep="")) %>%
      html_text()
    test <- c(test, x)
    if(identical(x, character(0))){
      test <- c(test, NaN)
    }
  }
  
  kozbesz[j,] <- test
  
  
  content = url %>% 
    html_nodes(xpath = "/html/body/div[7]/div/div[2]/div/div[2]") %>%
    html_text()
  
  if(identical(content, character(0))){
    penz <- c(penz, NaN)
    print(NaN)
  }
  else{
    
  

  splitted = unlist(strsplit(as.character(content), split = " ", fixed = TRUE))
  if(identical(grep("Érték:", splitted), integer(0))){
    penz <- c(penz, NaN)
    print(NaN)
  }
  else{
    ertek <- splitted[[grep("Érték:", splitted)+2]]
    print(ertek)
    penz <- c(penz, ertek)
  }
  
  }
}

kozbesz['Érték'] <- penz
