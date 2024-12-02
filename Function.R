


metac <- readRDS("metac.rds")

p = ggplot(as.data.frame(metac),
           aes(y = taxon_function_abun,
               axis1 = function., axis2 = Pathway_category, axis3 = taxon, axis4 = Disease)) +    
     geom_alluvium(aes(fill = Pathway_category), width = 3/5) +
     geom_stratum(aes(fill = Pathway_category), width = 3/5) +
     scale_fill_manual(values = colors) +
     geom_text(stat = "stratum", aes(label = after_stat(stratum)),
               size = 1.5, angle = 0) +
     scale_x_continuous(breaks = 1:4,
                        labels = c("Function pathways", "Pathway category", "Taxon", 'Disease'),
                        expand = c(0, 0)) +
     scale_y_continuous(expand = c(0, 0)) +
     labs(x = "", y = "Frequency") +
     theme_bw() +					
     theme(legend.position = "none",
           text = element_text(family = "serif", face = "bold", size = 10))










