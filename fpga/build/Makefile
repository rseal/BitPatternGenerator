FILENAME=TopModule

all: project xst ngd ncd ncd2 bit 

xst: 
	xst -ifn ${FILENAME}.cmd -ofn xst.log

ngd: 
	ngdbuild -nt timestamp -sd ../cores/ -p xc3s400-4pq208 ${FILENAME}

ncd: 
	rm -rf ${FILENAME}.ncd
	map -detail -c 10 -xe c -tx aggressive -logic_opt on -register_duplication on -equivalent_register_removal on -cm speed -retiming on -timing -ol high -p xc3s400-4pq208 -pr b ${FILENAME}.ngd -o ${FILENAME}.ncd ${FILENAME}.pcf

# Place and route ncd file into new ncd file
ncd2:	
	par -ol high -xe n -w ${FILENAME}.ncd ${FILENAME} ${FILENAME}.pcf

bit:	
	bitgen -w ${FILENAME}.ncd -b ../firmare/bpg.bit

#dpRamTest: ${FILENAME}.cpp buffer.h
#	g++ -o ${FILENAME} ${FILENAME}.cpp -lokFrontPanel -lusb -lblitz

clean:
	@rm -rf ${FILENAME}.ngc *.lst ../bin/$(FILENAME).bit *.lso *.xst *.stx *.syr \
	*.ngr *.cmd_log _ngc _xmsgs xst *.html *.srp \
	*.blc *.bld *.ise_ISE_Backup *~ *.prj  \
	*.pad *.ngm *.ngd *.par *.pcf *.unroutes     \
	*.xpi ../bin/$(FILENAME).bgn ../bin/$(FILENAME).drc *.bin *.mrp *.csv *.txt    \
	../bin/$(FILENAME).rbt *.ncd ${FILENAME} *_cg templates/ tmp/ \
        output.dat coregen.log *.ngo *.log TopModule.map \
	TopModule_summary.xml TopModule_usage.xml TopModule.twr \
	TopModule.cmd TopModule.psr TopModule.ptwx TopModule_map.xrpt \
	TopModule_ngdbuild.xrpt TopModule_par.xrpt TopModule_xst.xrpt \
	xlnx_auto_0.ise xlnx_auto_0_xdb/

project:
	@rm -rf ${FILENAME}.prj
	@echo '`define SPARTAN3 1'                 >> ${FILENAME}.prj
	@echo '`include "../hdl/${FILENAME}.v" '   >> ${FILENAME}.prj
	@echo '`include "../coregen/dpram.v"'      >> ${FILENAME}.prj
	@echo '`include "../coregen/ddpram.v"'     >> ${FILENAME}.prj
	@echo '`include "../coregen/lfsr.v"'       >> ${FILENAME}.prj
	@echo '`include "../hdl/InputControl.v"'   >> ${FILENAME}.prj
	@echo '`include "../hdl/OutputControl.v"'  >> ${FILENAME}.prj
	@echo '`include "../hdl/ClockDivider.v"'   >> ${FILENAME}.prj
	@echo '`include "../hdl/HeartBeat.v"'      >> ${FILENAME}.prj
	@echo '`include "../hdl/okLibrary.v"'      >> ${FILENAME}.prj
	@echo '`include "../hdl/ControlSignal.v"'  >> ${FILENAME}.prj
	@echo '`include "../hdl/StatusSignals.v"'  >> ${FILENAME}.prj
	@echo '`include "../hdl/DAC.v"'            >> ${FILENAME}.prj

command:
	rm -rf ${FILENAME}.cmd
	echo "identification"       >> ${FILENAME}.cmd
	echo "status"               >> ${FILENAME}.cmd
	echo "time short"           >> ${FILENAME}.cmd
	echo "memory on"            >> ${FILENAME}.cmd
	echo "run "	            >> ${FILENAME}.cmd
	echo "-top ${FILENAME}"     >> ${FILENAME}.cmd
	echo "-ifn ${FILENAME}.prj" >> ${FILENAME}.cmd
	echo "-ifmt Verilog "       >> ${FILENAME}.cmd
	echo "-ofn ${FILENAME} "    >> ${FILENAME}.cmd
	echo "-p xc3s400-4pq208"    >> ${FILENAME}.cmd
	echo "-vlgincdir { cores coregen}"  >> ${FILENAME}.cmd

