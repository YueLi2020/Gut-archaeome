

time place_seqs.py -s sequences.fasta -o placed_seqs.tre -p 50 -t sepp --intermediate intermediate/place_seqs

time hsp.py -i 16S -t placed_seqs.tre -o marker_nsti_predicted.tsv.gz -p 60 -n
zless -S marker_nsti_predicted.tsv.gz
time hsp.py -i EC -t placed_seqs.tre -o EC_predicted.tsv.gz -p 60
zless -S EC_predicted.tsv.gz
time hsp.py -i KO -t placed_seqs.tre -o KO_predicted.tsv.gz -p 60

time metagenome_pipeline.py -i feature-table.biom -m marker_nsti_predicted.tsv.gz -f EC_predicted.tsv.gz -o EC_metagenome_out --strat_out
zless -S EC_metagenome_out/pred_metagenome_unstrat.tsv.gz
zless -S EC_metagenome_out/pred_metagenome_contrib.tsv.gz
time metagenome_pipeline.py -i feature-table.biom -m marker_nsti_predicted.tsv.gz -f KO_predicted.tsv.gz -o KO_metagenome_out --strat_out
zless -S KO_metagenome_out/pred_metagenome_unstrat.tsv.gz
zless -S KO_metagenome_out/pred_metagenome_contrib.tsv.gz

time pathway_pipeline.py -i EC_metagenome_out/pred_metagenome_contrib.tsv.gz -o pathways_out -p 60
time pathway_pipeline.py -i EC_metagenome_out/pred_metagenome_unstrat.tsv.gz -o MetaCyc_pathways_out \
    -m /data/liyue/bin/picrust2/picrust2-2.4.2/picrust2/default_files/pathway_mapfiles/metacyc_path2rxn_struc_filt_pro.txt \
    --intermediate MetaCyc_pathways_out/minpath_working -p 60
time pathway_pipeline.py -i EC_metagenome_out/pred_metagenome_unstrat.tsv.gz -o MetaCyc_pathways_out_per_seq \
    --per_sequence_contrib --per_sequence_abun EC_metagenome_out/seqtab_norm.tsv.gz \
    --per_sequence_function EC_predicted.tsv.gz -p 60

time pathway_pipeline.py -i KO_metagenome_out/pred_metagenome_unstrat.tsv.gz -o KEGG_pathways_out --no_regroup \
    -m /data/liyue/bin/picrust2/picrust2-2.4.2/picrust2/default_files/pathway_mapfiles/KEGG_pathways_to_KO.tsv -p 60
time pathway_pipeline.py -i KO_metagenome_out/pred_metagenome_contrib.tsv.gz -o KEGG_pathways_out --no_regroup \
    -m /data/liyue/bin/picrust2/picrust2-2.4.2/picrust2/default_files/pathway_mapfiles/KEGG_pathways_to_KO.tsv -p 60

zless -S KEGG_pathways_out/path_abun_unstrat.tsv.gz

add_descriptions.py -i EC_metagenome_out/pred_metagenome_unstrat.tsv.gz -m EC -o EC_metagenome_out/pred_metagenome_unstrat_descrip.tsv.gz
add_descriptions.py -i KO_metagenome_out/pred_metagenome_unstrat.tsv.gz -m KO -o KO_metagenome_out/pred_metagenome_unstrat_descrip.tsv.gz
add_descriptions.py -i MetaCyc_pathways_out/path_abun_unstrat.tsv.gz -m METACYC -o MetaCyc_pathways_out/path_abun_unstrat_descrip.tsv.gz

add_descriptions.py -i KEGG_pathways_out/path_abun_unstrat.tsv.gz \
    --custom_map_table /data/liyue/bin/picrust2/picrust2-2.4.2/picrust2/default_files/description_mapfiles/KEGG_pathways_info.tsv.gz \
    -o KEGG_pathways_out/path_abun_unstrat_descrip.tsv.gz

zless -S EC_metagenome_out/pred_metagenome_unstrat_descrip.tsv.gz
zless -S KO_metagenome_out/pred_metagenome_unstrat_descrip.tsv.gz
zless -S KEGG_pathways_out/path_abun_unstrat_descrip.tsv.gz
zless -S MetaCyc_pathways_out/path_abun_unstrat_descrip.tsv.gz

